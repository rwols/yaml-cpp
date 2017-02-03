#ifndef DETAIL_ALL_TRUE_H
#define DETAIL_ALL_TRUE_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <type_traits>

namespace YAML {
namespace detail {

template <bool...>
struct bool_pack;

template <bool... bs>
using all_true = std::is_same<bool_pack<bs..., true>, bool_pack<true, bs...>>;

}  // namespace detail
}  // namespace YAML

#endif  // DETAIL_ALL_TRUE_H
