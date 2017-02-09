#ifndef NODE_CONVERT_DETAIL_FLOAT_TYPE_H
#define NODE_CONVERT_DETAIL_FLOAT_TYPE_H

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <limits>
#include <sstream>
#include <yaml-cpp/node/impl.h>

namespace YAML {
namespace detail {
namespace {

inline bool IsInfinity(const std::string& input) {
  return input == ".inf" || input == ".Inf" || input == ".INF" ||
         input == "+.inf" || input == "+.Inf" || input == "+.INF";
}

inline bool IsNegativeInfinity(const std::string& input) {
  return input == "-.inf" || input == "-.Inf" || input == "-.INF";
}

inline bool IsNaN(const std::string& input) {
  return input == ".nan" || input == ".NaN" || input == ".NAN";
}

}  // anonymous namespace

template <class T>
struct convert_float_type {
  static Node encode(const T& t) {
    std::ostringstream stream;
    stream.precision(std::numeric_limits<T>::digits10 + 1);
    stream << t;
    return Node(stream.str());
  }

  static bool decode(const Node& node, T& t) {
    if (!node.IsScalar())
      return false;
    const std::string& input = node.Scalar();
    std::istringstream stream(input);
    stream.unsetf(std::ios::dec);
    if ((stream >> std::noskipws >> t) && (stream >> std::ws).eof())
      return true;
    if (IsInfinity(input)) {
      t = std::numeric_limits<T>::infinity();
      return true;
    } else if (IsNegativeInfinity(input)) {
      t = -std::numeric_limits<T>::infinity();
      return true;
    } else if (IsNaN(input)) {
      t = std::numeric_limits<T>::quiet_NaN();
      return true;
    } else {
      return false;
    }
  }
};

}  // namespace detail
}  // namespace YAML

#endif  // NODE_CONVERT_DETAIL_FLOAT_TYPE_H
