#ifndef YAML_CPP_EMITTER_UNORDERED_MAP_H
#define YAML_CPP_EMITTER_UNORDERED_MAP_H

#include <unordered_map>
#include <yaml-cpp/emitter/detail/EmitSeq.h>

namespace YAML {

template <class Key, class T, class Hash, class KeyEqual, class Alloc>
Emitter& operator<<(
    Emitter& emit, const std::unordered_map<Key, T, Hash, KeyEqual, Alloc>& t) {
  return detail::EmitMap(emit, t);
}

}  // namespace YAML

#endif  // YAML_CPP_EMITTER_UNORDERED_MAP_H
