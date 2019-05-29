#pragma once
#ifndef AL2O3_PLATFORM_WIN_H
#define AL2O3_PLATFORM_WIN_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

//#	define _CRTDBG_MAP_ALLOC
//#	cppinclude <crtdbg.h>

#define AL2O3_EXPORT AL2O3_EXTERN_C __declspec(dllexport)
#define AL2O3_IMPORT AL2O3_EXTERN_C __declspec(dllimport)
#define AL2O3_EXPORT_CPP __declspec(dllexport)

#if __cplusplus >= 201103
#define AL2O3_DEFINE_ALIGNED(def, a) alignas(a) def
#else
#define AL2O3_DEFINE_ALIGNED(def, a) __declspec(align(a)) def
#endif

#endif // end AL2O3_PLATFORM_WIN_H