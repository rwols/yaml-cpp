#ifndef NODE_CONVERT_H_62B23520_7C8E_11DE_8A39_0800200C9A66
#define NODE_CONVERT_H_62B23520_7C8E_11DE_8A39_0800200C9A66

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <array>
#include <deque>
#include <forward_list>
#include <limits>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "yaml-cpp/binary.h"
#include "yaml-cpp/node/impl.h"
#include "yaml-cpp/node/iterator.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/type.h"
#include "yaml-cpp/null.h"

namespace YAML {
class Binary;
struct _Null;
template <typename T>
struct convert;
}  // namespace YAML

namespace YAML {
namespace conversion {
inline bool IsInfinity(const std::string& input) {
  return input == ".inf" || input == ".Inf" || input == ".INF" ||
         input == "+.inf" || input == "+.Inf" || input == "+.INF";
}

inline bool IsNegativeInfinity(const std::string& input) {
  return input == "-.inf" || input == "-.Inf" || input == "-.INF";
}

inline bool IsNaN(const std::string& input) {
  return input == ".nan" || input == ".NaN" || input == ".NAN";
}
}

// Node
template <>
struct convert<Node> {
  static Node encode(const Node& rhs) { return rhs; }

  static bool decode(const Node& node, Node& rhs) {
    rhs.reset(node);
    return true;
  }
};

// std::string
template <>
struct convert<std::string> {
  static Node encode(const std::string& rhs) { return Node(rhs); }

  static bool decode(const Node& node, std::string& rhs) {
    if (!node.IsScalar())
      return false;
    rhs = node.Scalar();
    return true;
  }
};

// C-strings can only be encoded
template <>
struct convert<const char*> {
  static Node encode(const char*& rhs) { return Node(rhs); }
};

template <std::size_t N>
struct convert<const char[N]> {
  static Node encode(const char(&rhs)[N]) { return Node(rhs); }
};

template <>
struct convert<_Null> {
  static Node encode(const _Null& /* rhs */) { return Node(); }

  static bool decode(const Node& node, _Null& /* rhs */) {
    return node.IsNull();
  }
};

#define YAML_DEFINE_CONVERT_STREAMABLE(type, negative_op)                \
  template <>                                                            \
  struct convert<type> {                                                 \
    static Node encode(const type& rhs) {                                \
      std::stringstream stream;                                          \
      stream.precision(std::numeric_limits<type>::digits10 + 1);         \
      stream << rhs;                                                     \
      return Node(stream.str());                                         \
    }                                                                    \
                                                                         \
    static bool decode(const Node& node, type& rhs) {                    \
      if (node.Type() != NodeType::Scalar)                               \
        return false;                                                    \
      const std::string& input = node.Scalar();                          \
      std::stringstream stream(input);                                   \
      stream.unsetf(std::ios::dec);                                      \
      if ((stream >> std::noskipws >> rhs) && (stream >> std::ws).eof()) \
        return true;                                                     \
      if (std::numeric_limits<type>::has_infinity) {                     \
        if (conversion::IsInfinity(input)) {                             \
          rhs = std::numeric_limits<type>::infinity();                   \
          return true;                                                   \
        } else if (conversion::IsNegativeInfinity(input)) {              \
          rhs = negative_op std::numeric_limits<type>::infinity();       \
          return true;                                                   \
        }                                                                \
      }                                                                  \
                                                                         \
      if (std::numeric_limits<type>::has_quiet_NaN &&                    \
          conversion::IsNaN(input)) {                                    \
        rhs = std::numeric_limits<type>::quiet_NaN();                    \
        return true;                                                     \
      }                                                                  \
                                                                         \
      return false;                                                      \
    }                                                                    \
  }

#define YAML_DEFINE_CONVERT_STREAMABLE_SIGNED(type) \
  YAML_DEFINE_CONVERT_STREAMABLE(type, -)

#define YAML_DEFINE_CONVERT_STREAMABLE_UNSIGNED(type) \
  YAML_DEFINE_CONVERT_STREAMABLE(type, +)

YAML_DEFINE_CONVERT_STREAMABLE_SIGNED(int);
YAML_DEFINE_CONVERT_STREAMABLE_SIGNED(short);
YAML_DEFINE_CONVERT_STREAMABLE_SIGNED(long);
YAML_DEFINE_CONVERT_STREAMABLE_SIGNED(long long);
YAML_DEFINE_CONVERT_STREAMABLE_UNSIGNED(unsigned);
YAML_DEFINE_CONVERT_STREAMABLE_UNSIGNED(unsigned short);
YAML_DEFINE_CONVERT_STREAMABLE_UNSIGNED(unsigned long);
YAML_DEFINE_CONVERT_STREAMABLE_UNSIGNED(unsigned long long);

YAML_DEFINE_CONVERT_STREAMABLE_SIGNED(char);
YAML_DEFINE_CONVERT_STREAMABLE_SIGNED(signed char);
YAML_DEFINE_CONVERT_STREAMABLE_UNSIGNED(unsigned char);

YAML_DEFINE_CONVERT_STREAMABLE_SIGNED(float);
YAML_DEFINE_CONVERT_STREAMABLE_SIGNED(double);
YAML_DEFINE_CONVERT_STREAMABLE_SIGNED(long double);

#undef YAML_DEFINE_CONVERT_STREAMABLE_SIGNED
#undef YAML_DEFINE_CONVERT_STREAMABLE_UNSIGNED
#undef YAML_DEFINE_CONVERT_STREAMABLE

// bool
template <>
struct convert<bool> {
  static Node encode(bool rhs) { return rhs ? Node("true") : Node("false"); }

  YAML_CPP_API static bool decode(const Node& node, bool& rhs);
};

// std::map
template <typename K, typename V>
struct convert<std::map<K, V>> {
  static Node encode(const std::map<K, V>& rhs) {
    Node node(NodeType::Map);
    for (typename std::map<K, V>::const_iterator it = rhs.begin();
         it != rhs.end(); ++it)
      node.force_insert(it->first, it->second);
    return node;
  }

  static bool decode(const Node& node, std::map<K, V>& rhs) {
    if (!node.IsMap())
      return false;

    rhs.clear();
    for (const_iterator it = node.begin(); it != node.end(); ++it)
#if defined(__GNUC__) && __GNUC__ < 4
      // workaround for GCC 3:
      rhs[it->first.template as<K>()] = it->second.template as<V>();
#else
      rhs[it->first.as<K>()] = it->second.as<V>();
#endif
    return true;
  }
};

// std::unordered_map
template <class Key, class T, class Hash, class KeyEqual, class Alloc>
struct convert<std::unordered_map<Key, T, Hash, KeyEqual, Alloc>> {
  
  using value_type = std::unordered_map<Key, T, Hash, KeyEqual, Alloc>;

  static Node encode(const value_type& rhs) {
    Node node(NodeType::Map);
    for (const auto& kv : rhs) node.force_insert(kv.first, kv.second);
    return node;
  }

  static bool decode(const Node& node, value_type& rhs) {
    if (!node.IsMap())
      return false;

    rhs.clear();
    for (const auto& kv : node) {
#if defined(__GNUC__) && __GNUC__ < 4
      // workaround for GCC 3:
      rhs[kv.first.template as<Key>()] = kv.second.template as<T>();
#else
      rhs[kv.first.as<Key>()] = kv.second.as<T>();
#endif
    }
    return true;
  }
};

// std::set
// A set is a map where each value is null.
template <class Key, class Compare, class Alloc>
struct convert<std::set<Key, Compare, Alloc>> {

  using value_type = std::set<Key, Compare, Alloc>;

  static Node encode(const value_type& rhs) {
    Node node(NodeType::Map);
    for (const auto& item : rhs) node.force_insert(item, Null);
    return node;
  }

  static bool decode(const Node& node, value_type& rhs) {
    if (!node.IsMap())
      return false;

    rhs.clear();
    for (const auto& kv : node)
#if defined(__GNUC__) && __GNUC__ < 4
      // workaround for GCC 3:
      rhs.insert(kv.first.template as<Key>());
#else
      rhs.insert(kv.first.as<Key>());
#endif
    return true;
  }
};

// std::unordered_set
// A set is a map where each value is null.
template<class Key, class Hash, class KeyEqual, class Alloc>
struct convert<std::unordered_set<Key, Hash, KeyEqual, Alloc>> {

  using value_type = std::unordered_set<Key, Hash, KeyEqual, Alloc>;

  static Node encode(const value_type& rhs) {
    Node node(NodeType::Map);
    for (const auto& item : rhs) node.force_insert(item, Null);
    return node;
  }

  static bool decode(const Node& node, value_type& rhs) {
    if (!node.IsMap())
      return false;

    rhs.clear();
    for (const auto& kv : node)
#if defined(__GNUC__) && __GNUC__ < 4
      // workaround for GCC 3:
      rhs.insert(kv.first.template as<Key>());
#else
      rhs.insert(kv.first.as<Key>());
#endif
    return true;
  }
};

// std::vector
template <typename T>
struct convert<std::vector<T>> {
  static Node encode(const std::vector<T>& rhs) {
    Node node(NodeType::Sequence);
    for (typename std::vector<T>::const_iterator it = rhs.begin();
         it != rhs.end(); ++it)
      node.push_back(*it);
    return node;
  }

  static bool decode(const Node& node, std::vector<T>& rhs) {
    if (!node.IsSequence())
      return false;

    rhs.clear();
    for (const_iterator it = node.begin(); it != node.end(); ++it)
#if defined(__GNUC__) && __GNUC__ < 4
      // workaround for GCC 3:
      rhs.push_back(it->template as<T>());
#else
      rhs.push_back(it->as<T>());
#endif
    return true;
  }
};

// std::deque
template <class T, class Alloc>
struct convert<std::deque<T, Alloc>> {

  using value_type = std::deque<T, Alloc>;

  static Node encode(const value_type& rhs) {
    Node node(NodeType::Sequence);
    for (const auto& item : rhs) node.push_back(item);
    return node;
  }

  static bool decode(const Node& node, value_type& rhs) {
    if (!node.IsSequence())
      return false;

    rhs.clear();
    for (const auto& item : node)
#if defined(__GNUC__) && __GNUC__ < 4
      // workaround for GCC 3:
      rhs.push_back(item.template as<T>());
#else
      rhs.push_back(item.as<T>());
#endif
    return true;
  }
};

// std::list
template <typename T>
struct convert<std::list<T>> {
  static Node encode(const std::list<T>& rhs) {
    Node node(NodeType::Sequence);
    for (typename std::list<T>::const_iterator it = rhs.begin();
         it != rhs.end(); ++it)
      node.push_back(*it);
    return node;
  }

  static bool decode(const Node& node, std::list<T>& rhs) {
    if (!node.IsSequence())
      return false;

    rhs.clear();
    for (const_iterator it = node.begin(); it != node.end(); ++it)
#if defined(__GNUC__) && __GNUC__ < 4
      // workaround for GCC 3:
      rhs.push_back(it->template as<T>());
#else
      rhs.push_back(it->as<T>());
#endif
    return true;
  }
};

// std::forward_list
template <class T, class Alloc>
struct convert<std::forward_list<T, Alloc>> {
  static Node encode(const std::forward_list<T, Alloc>& rhs) {
    Node node(NodeType::Sequence);
    for (const auto& item : rhs) node.push_back(item);
    return node;
  }

  static bool decode(const Node& node, std::forward_list<T, Alloc>& rhs) {
    if (!node.IsSequence())
      return false;

    rhs.clear();

    // Walk the sequence backwards, because std::forward_list does not have
    // push_back, only push_front.
    for (std::size_t i = node.size() - 1; i != (std::size_t)-1; --i)
    {
#if defined(__GNUC__) && __GNUC__ < 4
      // workaround for GCC 3:
      rhs.push_front(node[i].template as<T>());
#else
      rhs.push_front(node[i].as<T>());
#endif
    }
    return true;
  }
};

// std::array
template <typename T, std::size_t N>
struct convert<std::array<T, N>> {
  static Node encode(const std::array<T, N>& rhs) {
    Node node(NodeType::Sequence);
    for (const auto& element : rhs) {
      node.push_back(element);
    }
    return node;
  }

  static bool decode(const Node& node, std::array<T, N>& rhs) {
    if (!isNodeValid(node)) {
      return false;
    }

    for (auto i = 0u; i < node.size(); ++i) {
#if defined(__GNUC__) && __GNUC__ < 4
      // workaround for GCC 3:
      rhs[i] = node[i].template as<T>();
#else
      rhs[i] = node[i].as<T>();
#endif
    }
    return true;
  }

 private:
  static bool isNodeValid(const Node& node) {
    return node.IsSequence() && node.size() == N;
  }
};

// std::pair
template <typename T, typename U>
struct convert<std::pair<T, U>> {
  static Node encode(const std::pair<T, U>& rhs) {
    Node node(NodeType::Sequence);
    node.push_back(rhs.first);
    node.push_back(rhs.second);
    return node;
  }

  static bool decode(const Node& node, std::pair<T, U>& rhs) {
    if (!node.IsSequence())
      return false;
    if (node.size() != 2)
      return false;

#if defined(__GNUC__) && __GNUC__ < 4
    // workaround for GCC 3:
    rhs.first = node[0].template as<T>();
#else
    rhs.first = node[0].as<T>();
#endif
#if defined(__GNUC__) && __GNUC__ < 4
    // workaround for GCC 3:
    rhs.second = node[1].template as<U>();
#else
    rhs.second = node[1].as<U>();
#endif
    return true;
  }
};

// std::multimap
// A multimap is a sequence of (sorted) key-value pairs.
template<class Key, class T, class Compare, class Alloc>
struct convert<std::multimap<Key, T, Compare, Alloc>> {

  using value_type = std::multimap<Key, T, Compare, Alloc>;

  static Node encode(const value_type& rhs) {
    Node node(NodeType::Sequence);
    for (const auto& kv : rhs) {
      node.push_back(std::make_pair(kv.first, kv.second));
    }
    return node;
  }

  static bool decode(const Node& node, value_type& rhs) {
    if (!node.IsSequence())
      return false;

    rhs.clear();
    for (const auto& item : node)
#if defined(__GNUC__) && __GNUC__ < 4
      // workaround for GCC 3:
      rhs.insert(item.template as<std::pair<Key, T>>());
#else
      rhs.insert(item.as<std::pair<Key, T>>());
#endif
    return true;
  }
};

// binary
template <>
struct convert<Binary> {
  static Node encode(const Binary& rhs) {
    return Node(EncodeBase64(rhs.data(), rhs.size()));
  }

  static bool decode(const Node& node, Binary& rhs) {
    if (!node.IsScalar())
      return false;

    std::vector<unsigned char> data = DecodeBase64(node.Scalar());
    if (data.empty() && !node.Scalar().empty())
      return false;

    rhs.swap(data);
    return true;
  }
};
}

#endif  // NODE_CONVERT_H_62B23520_7C8E_11DE_8A39_0800200C9A66
