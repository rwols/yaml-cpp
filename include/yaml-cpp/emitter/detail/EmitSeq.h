#ifndef YAML_CPP_EMITTER_DETAIL_EMITSEQ_H
#define YAML_CPP_EMITTER_DETAIL_EMITSEQ_H

#include <yaml-cpp/emitter.h>

namespace YAML {
namespace detail {

template <class SequenceLike>
Emitter& EmitSeq(Emitter& emit, const SequenceLike& sequence) {
  emit << BeginSeq;
  for (const auto& item : sequence)
    emit << item;
  emit << EndSeq;
  return emit;
}

}  // namespace detail
}  // namespace YAML

#endif  // YAML_CPP_EMITTER_DETAIL_EMITSEQ_H
