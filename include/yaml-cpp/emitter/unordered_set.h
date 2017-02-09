#ifndef YAML_CPP_EMITTER_UNORDERED_SET_H
#define YAML_CPP_EMITTER_UNORDERED_SET_H

#include <unordered_set>
#ifdef YAML_CPP_PYYAML_COMPATIBILITY
#include <yaml-cpp/emitter/detail/EmitSet.h>
#else
#include <yaml-cpp/emitter/detail/EmitSeq.h>
#endif

namespace YAML {

template <class Key, class Hash, class KeyEqual, class Alloc>
Emitter& operator<<(Emitter& emit,
                    const std::unordered_set<Key, Hash, KeyEqual, Alloc>& t) {

#ifdef YAML_CPP_PYYAML_COMPATIBILITY

  return detail::EmitSet(emit, t);

#else

  return detail::EmitSeq(emit, t);

#endif
}

}  // namespace YAML

#endif  // YAML_CPP_EMITTER_UNORDERED_SET_H
