#ifndef NODE_CONVERT_FORWARD_LIST_H
#define NODE_CONVERT_FORWARD_LIST_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <forward_list>
#include <yaml-cpp/node/impl.h>

namespace YAML {

template <class T, class Alloc>
struct convert<std::forward_list<T, Alloc>> {
  static Node encode(const std::forward_list<T, Alloc>& sequence) {
    Node node(NodeType::Sequence);
    for (const auto& item : sequence) {
      node.push_back(item);
    }
    return node;
  }

  static bool decode(const Node& node, std::forward_list<T, Alloc>& sequence) {
    if (!node.IsSequence())
      return false;

    sequence.clear();

    // Walk the node backwards, because std::forward_list does not have
    // push_back, only push_front.
    for (std::size_t i = node.size() - 1; i != (std::size_t)-1; --i) {
#if defined(__GNUC__) && __GNUC__ < 4
      // workaround for GCC 3:
      sequence.push_front(node[i].template as<T>());
#else
      sequence.push_front(node[i].as<T>());
#endif
    }
    return true;
  }
};

}  // namespace YAML

#endif  // NODE_CONVERT_FORWARD_LIST_H
