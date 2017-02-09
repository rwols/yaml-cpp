#ifndef YAML_CPP_EMITTER_DETAIL_EMITMAP_H
#define YAML_CPP_EMITTER_DETAIL_EMITMAP_H

namespace YAML {
namespace detail {

template <class MapLike>
Emitter& EmitMap(Emitter& emit, const MapLike& map) {
  emit << BeginMap;
  for (const auto& kv : map)
    emit << Key << kv.first << Value << kv.second;
  emit << EndMap;
  return emit;
}

}  // namespace detail
}  // namespace YAML

#endif  // YAML_CPP_EMITTER_DETAIL_EMITMAP_H
