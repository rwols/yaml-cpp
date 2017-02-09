/**
 * @file Declares the YAML::convert template class which, by default, has no
 *       implementation. This file also includes all template specializations
 *       for which there is a conversion implemented. The purpose of the
 *       YAML::convert template class is to separate the constructors of a
 *       YAML::Node and the YAML::Node::as specializations into separate files.
 *       Moreover, it's easy to define your own specialization this way.
 */

#ifndef NODE_CONVERT_H_62B23520_7C8E_11DE_8A39_0800200C9A66
#define NODE_CONVERT_H_62B23520_7C8E_11DE_8A39_0800200C9A66

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

// C++ primitive types (YAML scalars)
#include <yaml-cpp/node/convert/bool.h>
#include <yaml-cpp/node/convert/char.h>
#include <yaml-cpp/node/convert/double.h>
#include <yaml-cpp/node/convert/float.h>
#include <yaml-cpp/node/convert/int.h>
#include <yaml-cpp/node/convert/long.h>
#include <yaml-cpp/node/convert/long_double.h>
#include <yaml-cpp/node/convert/long_long.h>
#include <yaml-cpp/node/convert/short.h>
#include <yaml-cpp/node/convert/signed_char.h>
#include <yaml-cpp/node/convert/unsigned_char.h>
#include <yaml-cpp/node/convert/unsigned_int.h>
#include <yaml-cpp/node/convert/unsigned_long.h>
#include <yaml-cpp/node/convert/unsigned_long_long.h>
#include <yaml-cpp/node/convert/unsigned_short.h>
#include <yaml-cpp/node/convert/wchar_t.h>

// YAML scalars
#include <yaml-cpp/node/convert/bitset.h>
#include <yaml-cpp/node/convert/cstring.h>
#include <yaml-cpp/node/convert/string.h>
#include <yaml-cpp/node/convert/wstring.h>

// YAML sequences
#include <yaml-cpp/node/convert/array.h>
#include <yaml-cpp/node/convert/deque.h>
#include <yaml-cpp/node/convert/forward_list.h>
#include <yaml-cpp/node/convert/list.h>
#include <yaml-cpp/node/convert/pair.h>
#include <yaml-cpp/node/convert/set.h>
#include <yaml-cpp/node/convert/tuple.h>
#include <yaml-cpp/node/convert/unordered_set.h>
#include <yaml-cpp/node/convert/vector.h>

// YAML maps
#include <yaml-cpp/node/convert/map.h>
#include <yaml-cpp/node/convert/unordered_map.h>

// miscellaneous
#include <yaml-cpp/node/convert/binary.h>
#include <yaml-cpp/node/convert/node.h>
#include <yaml-cpp/node/convert/null.h>

namespace YAML {

/**
 * @brief      Conversion between a YAML::Node and any type T
 *
 * @tparam     T     The type to provide a conversion for
 *
 * @note       If you end up here with a compile error, it's most likely the
 *             case that you haven't defined a template specialization for your
 *             type T.
 */
template <typename T>
struct convert {
  static Node encode(T&);
  static bool decode(const Node&, const T&);
};

}  // namespace YAML

#endif  // NODE_CONVERT_H_62B23520_7C8E_11DE_8A39_0800200C9A66
