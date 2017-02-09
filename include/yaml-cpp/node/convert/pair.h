#ifndef NODE_CONVERT_PAIR_H
#define NODE_CONVERT_PAIR_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <array>
#include <yaml-cpp/node/impl.h>

namespace YAML {

template <class First, class Second>
struct convert<std::pair<First, Second>> {
  static Node encode(const std::pair<First, Second>& tup) {
    Node node(NodeType::Sequence);
    node.push_back(std::get<0>(tup));
    node.push_back(std::get<1>(tup));
    return node;
  }

  static bool decode(const Node& node, std::pair<First, Second>& tup) {
    if (!node.IsSequence() || node.size() != 2)
      return false;
    std::get<0>(tup) = node[0].template as<First>();
    std::get<1>(tup) = node[1].template as<Second>();
    return true;
  }
};

}  // namespace YAML

#endif  // NODE_CONVERT_PAIR_H
