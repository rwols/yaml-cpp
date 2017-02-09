#ifndef NODE_CONVERT_LONG_H
#define NODE_CONVERT_LONG_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <yaml-cpp/node/impl.h>

namespace YAML {

template <>
struct convert<long> {
  static Node encode(const long t) { return Node(std::to_string(t)); }

  YAML_CPP_API static bool decode(const Node& node, long& t);
};

}  // namespace YAML

#endif  // NODE_CONVERT_LONG_H
