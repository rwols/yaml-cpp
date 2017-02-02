#ifndef DETAIL_MAKE_VOID_H
#define DETAIL_MAKE_VOID_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

namespace YAML {
namespace detail {

template <typename... T>
struct make_void {
  typedef void type;
};

}  // namespace detail
}  // namespace YAML

#endif  // DETAIL_MAKE_VOID_H
