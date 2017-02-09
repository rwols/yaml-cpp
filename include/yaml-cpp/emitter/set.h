#ifndef YAML_CPP_EMITTER_SET_H
#define YAML_CPP_EMITTER_SET_H

#include <set>
#ifdef YAML_CPP_PYYAML_COMPATIBILITY
#include <yaml-cpp/emitter/detail/EmitSet.h>
#else
#include <yaml-cpp/emitter/detail/EmitSeq.h>
#endif

namespace YAML {

template <class Key, class Compare, class Alloc>
Emitter& operator<<(Emitter& emit, const std::set<Key, Compare, Alloc>& t) {

#ifdef YAML_CPP_PYYAML_COMPATIBILITY

  return detail::EmitSet(emit, t);

#else

  return detail::EmitSeq(emit, t);

#endif
}

}  // namespace YAML

#endif  // YAML_CPP_EMITTER_SET_H
