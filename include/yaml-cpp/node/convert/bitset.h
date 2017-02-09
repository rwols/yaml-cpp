#ifndef NODE_CONVERT_BITSET_H
#define NODE_CONVERT_BITSET_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <bitset>
#include <yaml-cpp/node/convert/string.h>

namespace YAML {

template <std::size_t N>
struct convert<std::bitset<N>> {
  using value_type = std::bitset<N>;

  static Node encode(const value_type& rhs) {
    return convert<std::string>::encode(rhs.to_string());
  }

  static bool decode(const Node& node, value_type& rhs) {
    std::string representation;

    if (!convert<std::string>::decode(node, representation))
      return false;
    if (representation.size() != N)
      return false;
    try {
      // bitset constructor will throw std:invalid_argument if the decoded
      // string contains characters other than 0 and 1.
      rhs = value_type(representation);
    } catch (const std::invalid_argument& /*error*/) {
      return false;
    }
    return true;
  }
};

}  // namespace YAML

#endif  // NODE_CONVERT_BITSET_H
