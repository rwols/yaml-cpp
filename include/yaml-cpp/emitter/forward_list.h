#ifndef YAML_CPP_EMITTER_FORWARD_LIST_H
#define YAML_CPP_EMITTER_FORWARD_LIST_H

#include <forward_list>
#include <yaml-cpp/emitter/detail/EmitSeq.h>

namespace YAML {

template <class T, class Alloc>
Emitter& operator<<(Emitter& emit, const std::forward_list<T, Alloc>& t) {
  return detail::EmitSeq(emit, t);
}

}  // namespace YAML

#endif  // YAML_CPP_EMITTER_FORWARD_LIST_H
