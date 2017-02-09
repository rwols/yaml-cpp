#ifndef NODE_CONVERT_LIST_H
#define NODE_CONVERT_LIST_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <list>
#include <yaml-cpp/node/convert/detail/convert_as_sequence.h>

namespace YAML {

template <class T, class Alloc>
struct convert<std::list<T, Alloc>>
    : public detail::convert_as_sequence<std::list<T, Alloc>> {};

}  // namespace YAML

#endif  // NODE_CONVERT_LIST_H
