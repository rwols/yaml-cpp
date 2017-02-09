#ifndef NODE_CONVERT_FLOAT_H
#define NODE_CONVERT_FLOAT_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <yaml-cpp/node/convert/detail/convert_float_type.h>

namespace YAML {

template <>
struct convert<float> : public detail::convert_float_type<float> {};

}  // namespace YAML

#endif  // NODE_CONVERT_FLOAT_H
