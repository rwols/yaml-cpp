#ifndef NODE_CONVERT_UNORDERED_MAP_H
#define NODE_CONVERT_UNORDERED_MAP_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <unordered_map>
#include <yaml-cpp/node/convert/detail/convert_as_map.h>

namespace YAML {

template <class Key, class T, class Hash, class KeyEqual, class Alloc>
struct convert<std::unordered_map<Key, T, Hash, KeyEqual, Alloc>>
    : public detail::convert_as_map<
          std::unordered_map<Key, T, Hash, KeyEqual, Alloc>> {};

}  // namespace YAML

#endif  // NODE_CONVERT_UNORDERED_MAP_H
