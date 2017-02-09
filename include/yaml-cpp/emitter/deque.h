#ifndef YAML_CPP_EMITTER_DEQUE_H
#define YAML_CPP_EMITTER_DEQUE_H

#include <deque>
#include <yaml-cpp/emitter/detail/EmitSeq.h>

namespace YAML {

template <class T, class Alloc>
Emitter& operator<<(Emitter& emit, const std::deque<T, Alloc>& t) {
  return detail::EmitSeq(emit, t);
}

}  // namespace YAML

#endif  // YAML_CPP_EMITTER_DEQUE_H
