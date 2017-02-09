#ifndef NODE_CONVERT_CHAR_H
#define NODE_CONVERT_CHAR_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <yaml-cpp/node/impl.h>

namespace YAML {

template <>
struct convert<char> {
  static Node encode(const char t) { return Node(std::string(1, t)); }

  static bool decode(const Node& node, char& t) {
    if (!node.IsScalar() || node.Scalar().size() != 1)
      return false;
    t = node.Scalar()[0];
    return true;
  }
};

}  // namespace YAML

#endif  // NODE_CONVERT_CHAR_H
