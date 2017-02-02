#ifndef DETAIL_IS_VALID_OPERATOR_EXPRESSION_H
#define DETAIL_IS_VALID_OPERATOR_EXPRESSION_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <type_traits>
#include <yaml-cpp/detail/make_void.h>

namespace YAML {
namespace detail {

// catch-all for all invalid expressions
template <template <typename...> class Op, typename T1, typename T2 = T1,
          typename = void>
struct is_valid_operator_expression : public std::false_type {};

// this is taken when we find a valid expression.
template <template <typename, typename> class Op, typename T1, typename T2>
struct is_valid_operator_expression<Op, T1, T2,
                                    typename make_void<Op<T1, T2>>::type>
    : public std::true_type {};

}  // namespace detail
}  // namespace YAML

#endif  // DETAIL_IS_VALID_OPERATOR_EXPRESSION_H
