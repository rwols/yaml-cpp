#ifndef YAML_CPP_EMITTER_BITSET_H
#define YAML_CPP_EMITTER_BITSET_H

#include <bitset>
#include <yaml-cpp/emitter.h>

namespace YAML {

template <std::size_t N>
Emitter& operator<<(Emitter& emit, const std::bitset<N>& bits) {
  return emit << bits.to_string();
}

}  // namespace YAML

#endif  // YAML_CPP_EMITTER_BITSET_H
