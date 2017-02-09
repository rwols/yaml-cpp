#ifndef YAML_CPP_EMITTER_ARRAY_H
#define YAML_CPP_EMITTER_ARRAY_H

#include <array>
#include <yaml-cpp/emitter/detail/EmitSeq.h>

namespace YAML {

template <class T, std::size_t N>
Emitter& operator<<(Emitter& emit, const std::array<T, N>& t) {
  return detail::EmitSeq(emit, t);
}

}  // namespace YAML

#endif  // YAML_CPP_EMITTER_ARRAY_H
