#ifndef NODE_CONVERT_WSTRING_H
#define NODE_CONVERT_WSTRING_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <string>
#include <yaml-cpp/node/node.h>

namespace YAML {

template <>
struct convert<std::wstring> {
  YAML_CPP_API static Node encode(const std::wstring& t);
  YAML_CPP_API static bool decode(const Node& node, std::wstring& t);
};

}  // namespace YAML

#endif  // NODE_CONVERT_WSTRING_H
