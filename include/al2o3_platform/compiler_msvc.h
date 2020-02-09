#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>

#define AL2O3_EXPORT AL2O3_EXTERN_C __declspec(dllexport)
#define AL2O3_IMPORT AL2O3_EXTERN_C __declspec(dllimport)
#define AL2O3_EXPORT_CPP __declspec(dllexport)

#if __cplusplus >= 201103
#define AL2O3_DEFINE_ALIGNED(def, a) alignas(a) def
#else
#define AL2O3_DEFINE_ALIGNED(def, a) __declspec(align(a)) def
#endif

#define AL2O3_THREAD_LOCAL __declspec(thread)
#define AL2O3_FORCE_INLINE __forceinline
#define AL2O3_RESTRICT __restrict
#define AL2O3_DEBUG_BREAK() __debugbreak()
