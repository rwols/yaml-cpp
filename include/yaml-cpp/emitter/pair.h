#ifndef YAML_CPP_EMITTER_PAIR_H
#define YAML_CPP_EMITTER_PAIR_H

#include <utility>
#include <yaml-cpp/emitter.h>

namespace YAML {

template <class First, class Second>
Emitter& operator<<(Emitter& emit, const std::pair<First, Second>& pair) {

#ifdef YAML_CPP_PYYAML_COMPATIBILITY

  emit << SecondaryTag("python/tuple");

#endif

  emit << BeginSeq << pair.first << pair.second << EndSeq;
  return emit;
}

}  // namespace YAML

#endif  // YAML_CPP_EMITTER_PAIR_H
