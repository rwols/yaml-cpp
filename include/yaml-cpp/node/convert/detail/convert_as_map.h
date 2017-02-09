#ifndef NODE_CONVERT_DETAIL_CONVERT_AS_MAP_H
#define NODE_CONVERT_DETAIL_CONVERT_AS_MAP_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <yaml-cpp/node/impl.h>

namespace YAML {
namespace detail {

// Helper class for converting something which is "map-like" to and from a Node.
template <class T, class Key = typename T::key_type,
          class Value = typename T::mapped_type>
struct convert_as_map {
  static Node encode(const T& map) {
    Node node(NodeType::Map);
    for (const auto& kv : map) {
      node.force_insert(kv.first, kv.second);
    }
    return node;
  }

  static bool decode(const Node& node, T& map) {
    if (!node.IsMap())
      return false;
    map.clear();
    for (const auto& kv : node) {
// if we're dealing with GCC (note: clang also defines __GNUC__)
#if defined(__GNUC__)
#if __GNUC__ < 4
      // gcc version < 4
      map.insert(std::make_pair(kv.first.template as<Key>(),
                                kv.second.template as<Value>()));
#elif __GNUC__ == 4 && __GNUC_MINOR__ < 8
      // 4.0 <= gcc version < 4.8
      map.insert(std::make_pair(kv.first.as<Key>(), kv.second.as<Value>()));
#else
      // 4.8 <= gcc version
      map.emplace(kv.first.as<Key>(), kv.second.as<Value>());
#endif  // __GNUC__ < 4
#else
      // for anything not GCC or clang...
      // probably some more #ifdef guards are needed for MSVC.
      map.emplace(kv.first.as<Key>(), kv.second.as<Value>());
#endif  // defined(__GNUC__)
    }
    return true;
  }
};

}  // namespace detail
}  // namespace YAML

#endif  // NODE_CONVERT_DETAIL_CONVERT_AS_MAP_H
