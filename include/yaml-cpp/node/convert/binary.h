#ifndef NODE_CONVERT_BINARY_H
#define NODE_CONVERT_BINARY_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <yaml-cpp/node/node.h>

namespace YAML {

class Binary;

template <>
struct convert<Binary> {
  YAML_CPP_API static Node encode(const Binary& rhs);
  YAML_CPP_API static bool decode(const Node& node, Binary& rhs);
};

}  // namespace YAML

#endif  // NODE_CONVERT_BINARY_H
