#ifndef YAML_CPP_EMITTER_MAP_H
#define YAML_CPP_EMITTER_MAP_H

#include <map>
#include <yaml-cpp/emitter/detail/EmitMap.h>

namespace YAML {

template <class Key, class T, class Compare, class Alloc>
Emitter& operator<<(Emitter& emit, const std::map<Key, T, Compare, Alloc>& t) {
  return detail::EmitMap(emit, t);
}

}  // namespace YAML

#endif  // YAML_CPP_EMITTER_MAP_H
