#pragma once

#ifdef __cplusplus
#define AL2O3_EXTERN_C extern "C"
#else //!__cplusplus
#define AL2O3_EXTERN_C
#endif // end !_cplusplus

// platform options
#define AL2O3_PLATFORM_WINDOWS    (0)
#define AL2O3_PLATFORM_APPLE_MAC  (1)
#define AL2O3_PLATFORM_IPHONE     (2)
#define AL2O3_PLATFORM_UNIX       (3)
#define AL2O3_PLATFORM_ANDROID    (4)
#define AL2O3_PLATFORM_UNKNOWN		(5)

// OS options
#define AL2O3_OS_CUSTOM         (0)
#define AL2O3_OS_WINDOWS        (1)
#define AL2O3_OS_OSX            (2)
#define AL2O3_OS_GNULINUX       (3)
#define AL2O3_OS_FREEBSD        (4)
#define AL2O3_OS_ANDROID        (5)

// compiler family
#define AL2O3_COMPILER_MSVC     (0)
#define AL2O3_COMPILER_GCC      (1)
#define AL2O3_COMPILER_CLANG    (2)
#define AL2O3_COMPILER_CUDA     (3)

// endianess
#define AL2O3_CPU_LITTLE_ENDIAN (0)
#define AL2O3_CPU_BIG_ENDIAN    (1)

#define AL2O3_CPU_X86           (0)
#define AL2O3_CPU_X64           (1)
#define AL2O3_CPU_ARM           (2)

//--------------------------------------------------------
// Identification and classification from Compiler Defines
// Most of this info is from http://predef.sourceforge.net
//--------------------------------------------------------

// Processor and endian-ness identification
#if defined( i386 ) || defined( __i386__ ) || defined( __i386 ) || \
    defined( _M_IX86 ) || defined( __X86__ ) || defined( _X86_ ) || \
    defined( __THW_INTEL__ ) || defined( __I86__ ) || defined( __INTEL__ )
#define AL2O3_CPU_FAMILY    AL2O3_CPU_X86
#define AL2O3_CPU_ENDIANESS AL2O3_CPU_LITTLE_ENDIAN
#define AL2O3_CPU_BIT_SIZE  32
#elif defined( _M_X64 ) || defined( __amd64__ ) || defined( __amd64 ) || \
    defined( __x86_64__ ) || defined( __x86_64 )
#define AL2O3_CPU_FAMILY    AL2O3_CPU_X64
#define AL2O3_CPU_ENDIANESS AL2O3_CPU_LITTLE_ENDIAN
#define AL2O3_CPU_BIT_SIZE  64

#elif defined(__aarch64__)

#define AL2O3_CPU_FAMILY	AL2O3_CPU_ARM
#if defined(__AARCH64EB__)
#define AL2O3_CPU_ENDIANESS	AL2O3_CPU_BIG_ENDIAN
#else
#define AL2O3_CPU_ENDIANESS	AL2O3_CPU_LITTLE_ENDIAN
#endif
#define AL2O3_CPU_BIT_SIZE	64

#elif defined( __arm__ ) || defined( __thumb__ ) || defined( __TARGET_ARCH_ARM ) || defined( __TARGET_ARCH_THUMB ) || defined( _ARM )

#define AL2O3_CPU_FAMILY   AL2O3_CPU_ARM
#if defined(__ARMEB__) || defined(__THUMBEB__)
#define AL2O3_CPU_ENDIANESS	AL2O3_CPU_BIG_ENDIAN
#else
#define AL2O3_CPU_ENDIANESS	AL2O3_CPU_LITTLE_ENDIAN
#endif
#define AL2O3_CPU_BIT_SIZE	32

#endif // end CPU Id


// compiler identifcation
#if defined( __clang__)

#define AL2O3_COMPILER                  AL2O3_COMPILER_CLANG
#include "al2o3_platform/compiler_clang.h"

#elif defined(__NVCC__)

#define AL203_COMPILER AL203_COMPILER_CUDA
#include "al2o3_platform/compiler_cuda.h"

#elif defined( _MSC_VER )

// compiler version used with above
#define AL2O3_MS_VS2012                 (12)
#define AL2O3_MS_VS2013                 (13)
#define AL2O3_MS_VS2015                 (15)
#define AL2O3_MS_VS2017                 (17)

// Minimum we support is VS 2012
#if _MSC_VER < 1800
#error Not supported
#endif // end _MSCVER < 1800

#define AL2O3_COMPILER	AL2O3_COMPILER_MSVC

#if _MSC_VER < 1800
#define AL2O3_COMPILER_VERSION		AL2O3_MS_VS2012
#elif _MSC_VER < 1900
#define AL2O3_COMPILER_VERSION		AL2O3_MS_VS2013
#elif _MSC_VER < 1910
#define AL2O3_COMPILER_VERSION		AL2O3_MS_VS2015
#else
#define AL2O3_COMPILER_VERSION		AL2O3_MS_VS2017
#endif

#include "al2o3_platform/compiler_msvc.h"


#elif defined( __GNUC__ )
#define AL2O3_COMPILER				  AL2O3_COMPILER_GCC
#define AL2O3_GCC_V2                    (0)
#define AL2O3_GCC_V3                    (1)
#define AL2O3_GCC_V4                    (2)
#define AL2O3_GCC_V4_3                  (3)

#include "al2o3_platform/compiler_gcc.h"

#else
#error Not supported
#endif

// OS
#if defined( WIN32 )

#	define AL2O3_PLATFORM 				AL2O3_PLATFORM_WINDOWS
#	define AL2O3_PLATFORM_OS			AL2O3_OS_WINDOWS

#include "al2o3_platform/platform_win.h"

#elif defined(__APPLE__) && defined( __MACH__ )

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE
#define AL2O3_PLATFORM    AL2O3_PLATFORM_IPHONE
#else
#define AL2O3_PLATFORM    AL2O3_PLATFORM_APPLE_MAC
#endif
#define AL2O3_PLATFORM_OS AL2O3_OS_OSX

// override endianness with the OS_OSX one, hopefully right...
#undef AL2O3_CPU_ENDIANESS
#define AL2O3_CPU_ENDIANESS (TARGET_RT_LITTLE_ENDIAN == 1)

#include "al2o3_platform/platform_osx.h"

#elif defined(__ANDROID__)

#define AL2O3_PLATFORM      AL2O3_PLATFORM_ANDROID
#define AL2O3_PLATFORM_OS	AL2O3_OS_ANDROID

#include "al2o3_platform/platform_android.h"

#elif    defined( __unix__ ) || defined( __unix ) || \
        defined( __sysv__ ) || defined( __SVR4 ) || defined( __svr4__ ) || defined( _SYSTYPE_SVR4 ) || \
        defined( __FreeBSD__ ) || defined( __NetBSD__ ) || defined( __OpenBSD__ ) || defined( __bsdi__ ) || defined ( __DragonFly__ ) || defined( _SYSTYPE_BSD ) || \
        defined( sco ) || defined( _UNIXWARE7 ) || defined( ultrix ) || defined( __ultrix ) || defined( __ultrix__ ) || \
        defined( __osf__ ) || defined( __osf ) || defined( sun ) || defined( __sun ) || \
        defined( M_XENIX ) || defined( _SCO_DS ) || defined( sinux ) || defined( __minix ) || \
        defined( linux ) || defined( __linux ) || \
        defined( sgi ) || defined( __sgi ) || defined( __BEOS__ ) || defined (_AIX )

#define AL2O3_PLATFORM AL2O3_PLATFORM_UNIX

#if defined( linux ) || defined( __linux )

#define AL2O3_PLATFORM_OS AL2O3_OS_GNULINUX
#include "al2o3_platform/platform_linux.h"

#elif defined( __FreeBSD__ ) || defined( __NetBSD__ ) || defined( __OpenBSD__ ) || defined( __bsdi__ ) || defined ( __DragonFly__ ) || defined( _SYSTYPE_BSD )

#define AL2O3_PLATFORM_OS		AL2O3_OS_FREEBSD
#include "al2o3_platform/platform_posix.h"

#else // unknown unix
#error Not supported
#endif

#else // unknown PLATFORM

#define AL2O3_PLATFORM AL2O3_PLATFORM_UNKNOWN

//#error UKNOWN_PLATFORM
#endif // endif OS

#include "al2o3_platform/debug.h"

#ifndef AL2O3_LINK_OR_INLINE
#define AL2O3_LINK_OR_INLINE AL2O3_EXTERN_C AL2O3_FORCE_INLINE
#endif
