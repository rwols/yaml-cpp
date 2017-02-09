#ifndef NODE_CONVERT_SET_H
#define NODE_CONVERT_SET_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <set>
#include <yaml-cpp/node/convert/detail/convert_as_set.h>

namespace YAML {

template <class Key, class Compare, class Alloc>
struct convert<std::set<Key, Compare, Alloc>>
    : public detail::convert_as_set<std::set<Key, Compare, Alloc>> {};

}  // namespace YAML

#endif  // NODE_CONVERT_SET_H
