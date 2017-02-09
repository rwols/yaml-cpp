#ifndef NODE_CONVERT_ARRAY_H
#define NODE_CONVERT_ARRAY_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <array>
#include <yaml-cpp/node/impl.h>

namespace YAML {

template <typename T, std::size_t N>
struct convert<std::array<T, N>> {
  static Node encode(const std::array<T, N>& sequence) {
    Node node(NodeType::Sequence);
    for (const auto& item : sequence) {
      node.push_back(item);
    }
    return node;
  }

  static bool decode(const Node& node, std::array<T, N>& sequence) {
    if (!isNodeValid(node)) {
      return false;
    }

    for (auto i = 0u; i < node.size(); ++i) {
#if defined(__GNUC__) && __GNUC__ < 4
      // workaround for GCC 3:
      sequence[i] = node[i].template as<T>();
#else
      sequence[i] = node[i].as<T>();
#endif
    }
    return true;
  }

 private:
  static bool isNodeValid(const Node& node) {
    return node.IsSequence() && node.size() == N;
  }
};

}  // namespace YAML

#endif  // NODE_CONVERT_ARRAY_H
