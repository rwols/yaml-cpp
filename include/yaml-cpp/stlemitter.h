#ifndef STLEMITTER_H_62B23520_7C8E_11DE_8A39_0800200C9A66
#define STLEMITTER_H_62B23520_7C8E_11DE_8A39_0800200C9A66

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <array>
#include <bitset>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <set>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <yaml-cpp/detail/all_true.h>
#include <yaml-cpp/detail/has_left_shift.h>

namespace YAML {

// if the expression `emitter << myvalue;` is valid,
// then we consider it a yaml scalar.
template <class T>
struct IsOutputScalar : public detail::has_left_shift<Emitter&, const T&> {};

// nothing is a sequence by default.
template <class T>
struct IsOutputSequence : public std::false_type {};

// nothing is a map by default.
template <class T>
struct IsOutputMap : public std::false_type {};

// a primitive is a scalar or a sequence or a map.
template <class T>
struct IsOutputPrimitive {
  static constexpr bool value = IsOutputScalar<T>::value ||
                                IsOutputSequence<T>::value ||
                                IsOutputMap<T>::value;
};

template <class... Ts>
using AllOutputPrimitive = detail::all_true<IsOutputPrimitive<Ts>::value...>;

// std::vector
// is an output sequence if and only if T is a primitive.
template <class T, class Alloc>
struct IsOutputSequence<std::vector<T, Alloc>> {
  static constexpr bool value = IsOutputPrimitive<T>::value;
};

// std::list
// is an output sequence if and only if T is a primitive.
template <class T, class Alloc>
struct IsOutputSequence<std::list<T, Alloc>> {
  static constexpr bool value = IsOutputPrimitive<T>::value;
};

// std::deque
// is an output sequence if and only if T is a primitive.
template <class T, class Alloc>
struct IsOutputSequence<std::deque<T, Alloc>> {
  static constexpr bool value = IsOutputPrimitive<T>::value;
};

// std::forward_list
// is an output sequence if and only if T is a primitive.
template <class T, class Alloc>
struct IsOutputSequence<std::forward_list<T, Alloc>> {
  static constexpr bool value = IsOutputPrimitive<T>::value;
};

// std::array
// is an output sequence if and only if T is a primitive.
template <class T, std::size_t N>
struct IsOutputSequence<std::array<T, N>> {
  static constexpr bool value = IsOutputPrimitive<T>::value;
};

// std::map
// is an output map if and only if both Key and T are primitives.
template <class Key, class T, class Compare, class Alloc>
struct IsOutputMap<std::map<Key, T, Compare, Alloc>> {
  static constexpr bool value = AllOutputPrimitive<Key, T>::value;
};

// std::unordered_map
// is an output map if and only if both Key and T are primitives.
template <class Key, class T, class Hash, class KeyEqual, class Alloc>
struct IsOutputMap<std::unordered_map<Key, T, Hash, KeyEqual, Alloc>> {
  static constexpr bool value = AllOutputPrimitive<Key, T>::value;
};

// std::multimap
// is an output sequence if and only if both Key and T are primitives.
template <class Key, class T, class Compare, class Alloc>
struct IsOutputSequence<std::multimap<Key, T, Compare, Alloc>> {
  static constexpr bool value = AllOutputPrimitive<Key, T>::value;
};

// std::unordered_multimap
// is an output sequence if and only if both Key and T are primitives.
template <class Key, class T, class Hash, class KeyEqual, class Alloc>
struct IsOutputSequence<
    std::unordered_multimap<Key, T, Hash, KeyEqual, Alloc>> {
  static constexpr bool value = AllOutputPrimitive<Key, T>::value;
};

// std::set
// is an output sequence if and only if Key is a primitive.
template <class Key, class Compare, class Alloc>
struct IsOutputSequence<std::set<Key, Compare, Alloc>> {
  static constexpr bool value = IsOutputPrimitive<Key>::value;
};

// std::unordered_set
// is an output sequence if and only if Key is a primitive.
template <class Key, class Hash, class KeyEqual, class Alloc>
struct IsOutputSequence<std::unordered_set<Key, Hash, KeyEqual, Alloc>> {
  static constexpr bool value = IsOutputPrimitive<Key>::value;
};

// std::pair
// is a yaml scalar (because we define `<<`) provided that First and Second are
// primitives.
template <class First, class Second>
typename std::enable_if<IsOutputPrimitive<First>::value &&
                            IsOutputPrimitive<Second>::value,
                        Emitter&>::type
    operator<<(Emitter& emitter, const std::pair<First, Second>& pair) {
  return emitter << BeginSeq << pair.first << pair.second << EndSeq;
}

// std::bitset
// is a yaml scalar (because we define `<<`).
template <std::size_t N>
Emitter& operator<<(Emitter& emitter, const std::bitset<N>& bits) {
  return emitter << bits.to_string();
}

// The emitter knows what to do with an output sequence (possibly recursive).
template <class T>
typename std::enable_if<IsOutputSequence<T>::value, Emitter&>::type operator<<(
    Emitter& emitter, const T& sequence) {
  emitter << BeginSeq;
  for (const auto& item : sequence)
    emitter << item;
  emitter << EndSeq;
  return emitter;
}

// The emitter knows what to do with an output map (possibly recursive).
template <class T>
typename std::enable_if<IsOutputMap<T>::value, Emitter&>::type operator<<(
    Emitter& emitter, const T& map) {
  emitter << BeginMap;
  for (const auto& kv : map)
    emitter << Key << kv.first << Value << kv.second;
  emitter << EndMap;
  return emitter;
}

namespace detail {

template <std::size_t Index = 0, typename... Args>
typename std::enable_if<Index == sizeof...(Args)>::type EmitTuple(
    Emitter& /*emitter*/, const std::tuple<Args...>& /*tup*/) {}

template <std::size_t Index = 0, typename... Args>
typename std::enable_if<Index != sizeof...(Args)>::type EmitTuple(
    Emitter& emitter, const std::tuple<Args...>& tup) {
  emitter << std::get<Index>(tup);
  EmitTuple<Index + 1, Args...>(emitter, tup);
}

}  // namespace detail

// std::tuple
template <typename... Args>
// typename std::enable_if<AllOutputPrimitive<Args...>::value, Emitter&>::type
Emitter& operator<<(Emitter& emitter, const std::tuple<Args...>& tup) {
  emitter << BeginSeq;
  detail::EmitTuple(emitter, tup);
  emitter << EndSeq;
  return emitter;
}

// std::tuple -- empty
inline Emitter& operator<<(Emitter& emitter, const std::tuple<>& /*tup*/) {
  emitter << Null;
  return emitter;
}

}  // namespace YAML

#endif  // STLEMITTER_H_62B23520_7C8E_11DE_8A39_0800200C9A66
