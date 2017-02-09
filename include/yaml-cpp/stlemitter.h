#ifndef STLEMITTER_H_62B23520_7C8E_11DE_8A39_0800200C9A66
#define STLEMITTER_H_62B23520_7C8E_11DE_8A39_0800200C9A66

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

// YAML scalars
#include <yaml-cpp/emitter/bitset.h>

// YAML sequences
#include <yaml-cpp/emitter/array.h>
#include <yaml-cpp/emitter/deque.h>
#include <yaml-cpp/emitter/forward_list.h>
#include <yaml-cpp/emitter/list.h>
#include <yaml-cpp/emitter/pair.h>
#include <yaml-cpp/emitter/set.h>
#include <yaml-cpp/emitter/tuple.h>
#include <yaml-cpp/emitter/unordered_set.h>
#include <yaml-cpp/emitter/vector.h>

// YAML maps
#include <yaml-cpp/emitter/map.h>
#include <yaml-cpp/emitter/unordered_map.h>

#endif  // STLEMITTER_H_62B23520_7C8E_11DE_8A39_0800200C9A66
