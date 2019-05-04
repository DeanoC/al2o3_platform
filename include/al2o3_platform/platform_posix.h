#pragma once
#ifndef AL2O3_PLATFORM_POSIX_H
#define AL2O3_PLATFORM_POSIX_H

#ifndef _RUST_BINDGEN_
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>
#include <strings.h>
else
	typedef unsigned long size_t;
#endif


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

#define stricmp(a, b) strcasecmp(a, b)
#define vsprintf_s vsnprintf
#define strncpy_s strncpy
#define _strdup strdup

#endif // AL2O3_PLATFORM_POSIX_H