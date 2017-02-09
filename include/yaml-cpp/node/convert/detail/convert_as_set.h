#ifndef NODE_CONVERT_DETAIL_CONVERT_AS_SET_H
#define NODE_CONVERT_DETAIL_CONVERT_AS_SET_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <yaml-cpp/node/impl.h>

namespace YAML {
namespace detail {

// Helper class for converting something which is "set-like" to and from a Node.
// A set is realized as a yaml sequence by default, but if
// YAML_CPP_PYYAML_COMPATIBILITY is defined, it is realized as yaml map where
// each value is null, and it has a local tag "set" attached to it.
template <class T>
struct convert_as_set {
  static Node encode(const T& set) {

#ifdef YAML_CPP_PYYAML_COMPATIBILITY

    Node node(NodeType::Map);
    node.SetTag("set");
    for (const auto& item : set) {
      node.force_insert(item, Null);
    }

#else

    Node node(NodeType::Sequence);
    for (const auto& item : set) {
      node.push_back(item);
    }

#endif  // YAML_CPP_PYYAML_COMPATIBILITY

    return node;
  }

  static bool decode(const Node& node, T& set) {

#ifdef YAML_CPP_PYYAML_COMPATIBILITY

    if (!node.IsMap())
      return false;
    if (node.Tag().find("set") == std::string::npos)
      return false;
    set.clear();
    for (const auto& kv : node) {
      if (!kv.second.IsNull())
        return false;
      set.insert(kv.first.template as<typename T::value>());
    }

#else

    if (!node.IsSequence())
      return false;
    set.clear();
    for (const auto& item : node) {
      set.insert(item.template as<typename T::value_type>());
    }

#endif  // YAML_CPP_PYYAML_COMPATIBILITY

    return true;
  }
};

}  // namespace detail
}  // namespace YAML

#endif  // NODE_CONVERT_DETAIL_CONVERT_AS_SET_H
