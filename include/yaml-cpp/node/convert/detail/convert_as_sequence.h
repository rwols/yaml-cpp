#ifndef NODE_CONVERT_DETAIL_CONVERT_AS_SEQUENCE_H
#define NODE_CONVERT_DETAIL_CONVERT_AS_SEQUENCE_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <yaml-cpp/node/impl.h>

namespace YAML {
namespace detail {

// Helper class for converting something which is "sequence-like" to and from a
// Node.
template <class T>
struct convert_as_sequence {
  static Node encode(const T& sequence) {
    Node node(NodeType::Sequence);
    for (const auto& item : sequence) {
      node.push_back(item);
    }
    return node;
  }
  static bool decode(const Node& node, T& sequence) {
    if (!node.IsSequence())
      return false;
    sequence.clear();
    for (const auto& item : node) {
      sequence.push_back(item.template as<typename T::value_type>());
    }
    return true;
  }
};

}  // namespace detail
}  // namespace YAML

#endif  // NODE_CONVERT_DETAIL_CONVERT_AS_SEQUENCE_H
