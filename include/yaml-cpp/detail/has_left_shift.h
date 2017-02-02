#ifndef DETAIL_HAS_LEFT_SHIFT_H
#define DETAIL_HAS_LEFT_SHIFT_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <yaml-cpp/detail/is_valid_operator_expression.h>

namespace YAML {
namespace detail {

template <typename L, typename R>
using left_shift_t = decltype(std::declval<L>() << std::declval<R>());

template <typename L, typename R>
struct has_left_shift : is_valid_operator_expression<left_shift_t, L, R> {};

}  // namespace detail
}  // namespace YAML

#endif  // DETAIL_HAS_LEFT_SHIFT_H
