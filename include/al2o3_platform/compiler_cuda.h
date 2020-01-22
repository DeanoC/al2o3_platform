// License Summary: MIT see LICENSE file
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>

#define AL2O3_DEFINE_ALIGNED(def, a) alignas(a) def

#define AL2O3_EXPORT AL2O3_EXTERN_C
#define AL2O3_IMPORT AL2O3_EXTERN_C
#define AL2O3_EXPORT_CPP
#define AL2O3_THREAD_LOCAL __thread
#define AL2O3_FORCE_INLINE inline
#define AL2O3_RESTRICT __restrict

#ifndef __has_builtin         // Optional of course.
#define __has_builtin(x) 0  // Compatibility with non-clang compilers.
#endif

#if __has_builtin(__builtin_trap)
#define AL2O3_DEBUG_BREAK() __builtin_trap();
#else
#define AL2O3_DEBUG_BREAK()
#endif
