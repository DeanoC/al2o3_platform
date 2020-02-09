// License Summary: MIT see LICENSE file
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>

#if __cplusplus >= 201103
#define AL2O3_DEFINE_ALIGNED(def, a) alignas(a) def
#elif defined(__OSX__)
#define AL2O3_DEFINE_ALIGNED(def, a) def __attribute__((aligned(a)))
#else
#define AL2O3_DEFINE_ALIGNED(def, a) def __align__(a)
#endif

#define AL2O3_EXPORT AL2O3_EXTERN_C
#define AL2O3_IMPORT AL2O3_EXTERN_C
#define AL2O3_EXPORT_CPP
#define AL2O3_THREAD_LOCAL __thread
#define AL2O3_FORCE_INLINE inline __attribute__((always_inline))
#define AL2O3_RESTRICT __restrict
#define stricmp(a, b) strcasecmp(a, b)

#ifndef __has_builtin         // Optional of course.
#define __has_builtin(x) 0  // Compatibility with non-clang compilers.
#endif

#if __has_builtin(__builtin_trap)
#define AL2O3_DEBUG_BREAK() __builtin_trap();
#elif AL2O3_COMPILER == AL2O3_COMPILER_CLANG
#define AL2O3_DEBUG_BREAK() __builtin_trap();
#elif AL2O3_COMPILER == AL2O3_COMPILER_GCC
#define AL2O3_DEBUG_BREAK() __builtin_trap();
#else
#define AL2O3_DEBUG_BREAK() __asm int 3
#endif
