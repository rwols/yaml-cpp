#ifndef NODE_CONVERT_WCHAR_T_H
#define NODE_CONVERT_WCHAR_T_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <yaml-cpp/node/node.h>

namespace YAML {

template <>
struct convert<wchar_t> {
  YAML_CPP_API static Node encode(const wchar_t t);
  YAML_CPP_API static bool decode(const Node& node, wchar_t& t);
};

}  // namespace YAML

#endif  // NODE_CONVERT_WCHAR_T_H
