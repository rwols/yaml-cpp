#ifndef NODE_CONVERT_UNORDERED_SET_H
#define NODE_CONVERT_UNORDERED_SET_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <unordered_set>
#include <yaml-cpp/node/convert/detail/convert_as_set.h>

namespace YAML {

template <class Key, class Hash, class KeyEqual, class Alloc>
struct convert<std::unordered_set<Key, Hash, KeyEqual, Alloc>>
    : public detail::convert_as_set<
          std::unordered_set<Key, Hash, KeyEqual, Alloc>> {};

}  // namespace YAML

#endif  // NODE_CONVERT_UNORDERED_SET_H
