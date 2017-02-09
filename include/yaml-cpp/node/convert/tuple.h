#ifndef NODE_CONVERT_TUPLE_H
#define NODE_CONVERT_TUPLE_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <tuple>
#include <yaml-cpp/node/convert/null.h>

namespace YAML {
namespace detail {

template <std::size_t Index = 0, typename... Args>
inline typename std::enable_if<Index == sizeof...(Args), void>::type
    encode_tuple(Node& /*node*/, const std::tuple<Args...>& /*tup*/) {}

template <std::size_t Index = 0, typename... Args>
inline typename std::enable_if<Index != sizeof...(Args), void>::type
    encode_tuple(Node& node, const std::tuple<Args...>& tup) {
  node.push_back(std::get<Index>(tup));
  encode_tuple<Index + 1, Args...>(node, tup);
}

template <std::size_t Index = 0, typename... Args>
inline typename std::enable_if<Index == sizeof...(Args), void>::type
    decode_tuple(const Node& /*node*/, std::tuple<Args...>& /*tup*/) {}

template <std::size_t Index = 0, typename... Args>
inline typename std::enable_if<Index != sizeof...(Args), void>::type
    decode_tuple(const Node& node, std::tuple<Args...>& tup) {
  std::get<Index>(tup) =
      node[Index]
          .template as<
              typename std::tuple_element<Index, std::tuple<Args...>>::type>();
  decode_tuple<Index + 1, Args...>(node, tup);
}

}  // namespace detail

// std::tuple
template <typename... Args>
struct convert<std::tuple<Args...>> {
  static Node encode(const std::tuple<Args...>& tup) {
    static_assert(sizeof...(Args) > 0,
                  "wrong template specialization selected");
    Node node(NodeType::Sequence);
    detail::encode_tuple(node, tup);
    return node;
  }

  static bool decode(const Node& node, std::tuple<Args...>& tup) {
    static_assert(sizeof...(Args) > 0,
                  "wrong template specialization selected");
    if (!node.IsSequence() || node.size() != sizeof...(Args))
      return false;
    detail::decode_tuple(node, tup);
    return true;
  }
};

// std::tuple -- empty
template <>
struct convert<std::tuple<>> {
  static Node encode(const std::tuple<>& /*tup*/) {
    return convert<_Null>::encode(Null);
  }
  static bool decode(const Node& node, std::tuple<>& /*tup*/) {
    return convert<_Null>::decode(node, Null);
  }
};

}  // namespace YAML

#endif  // NODE_CONVERT_TUPLE_H
