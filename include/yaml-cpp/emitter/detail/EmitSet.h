#ifndef YAML_CPP_EMITTER_DETAIL_EMITSET_H
#define YAML_CPP_EMITTER_DETAIL_EMITSET_H

namespace YAML {
namespace detail {

template <class SetLike>
Emitter& EmitSet(Emitter& emit, const SetLike& set) {

#ifdef YAML_CPP_PYYAML_COMPABILITITY

  emit << SecondaryTag("set");

#endif

  emit << BeginMap;
  for (const auto& item : set) {
    emit << Key << item << Value << Null;
  }
  emit << EndMap;
  return emit;
}

}  // namespace detail
}  // namespace YAML

#endif  // YAML_CPP_EMITTER_DETAIL_EMITSET_H
