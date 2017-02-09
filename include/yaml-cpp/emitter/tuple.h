#ifndef YAML_CPP_EMITTER_TUPLE_H
#define YAML_CPP_EMITTER_TUPLE_H

#include <tuple>
#include <yaml-cpp/emitter.h>

namespace YAML {
namespace detail {

template <std::size_t Index = 0, typename... Args>
typename std::enable_if<Index == sizeof...(Args), Emitter&>::type EmitTuple(
    Emitter& emit, const std::tuple<Args...>& /*tup*/) {
  return emit;
}

template <std::size_t Index = 0, typename... Args>
typename std::enable_if<Index != sizeof...(Args), Emitter&>::type EmitTuple(
    Emitter& emit, const std::tuple<Args...>& tup) {
  emit << std::get<Index>(tup);
  return EmitTuple<Index + 1, Args...>(emit, tup);
}

}  // namespace detail

template <typename... Args>
Emitter& operator<<(Emitter& emit, const std::tuple<Args...>& tup) {

#ifdef YAML_CPP_PYYAML_COMPATIBILITY

  emit << SecondaryTag("python/tuple");

#endif

  emit << BeginSeq;
  detail::EmitTuple(emit, tup);
  emit << EndSeq;
  return emit;
}

inline Emitter& operator<<(Emitter& emit, const std::tuple<>& /*tup*/) {

#ifdef YAML_CPP_PYYAML_COMPATIBILITY

  emit << SecondaryTag("python/tuple");

#endif

  emit << Null;
  return emit;
}

}  // namespace YAML

#endif  // YAML_CPP_EMITTER_TUPLE_H
