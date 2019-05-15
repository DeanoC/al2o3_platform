#pragma once
#ifndef AL2O3_PLATFORM_DEBUG_H
#define AL2O3_PLATFORM_DEBUG_H

#include "al2o3_platform/platform.h"

#ifndef USE_LOGGING
#define USE_LOGGING 1
#endif // end USE_LOGGING

typedef struct AL2O3_Logger_t {
	// lowest level of logging, (file, line, message)
	void (*errorMsg)(char const* file, int line, const char* function, char const* msg);
	void (*warningMsg)(char const* file, int line, const char* function, char const* msg);
	void (*infoMsg)(char const* file, int line, const char* function, char const* msg);
	void (*debugMsg)(char const* file, int line, const char* function, char const* msg);

	void (*failedAssert)(char const* file, int line, const char* function, char const* statement);
} AL2O3_Logger_t;

AL2O3_EXTERN_C AL2O3_Logger_t AL2O3_Logger;

AL2O3_EXTERN_C void AL2O3_OutputDebug(char const *msg);

AL2O3_EXTERN_C void AL2O3_ErrorMsg(const char* file, int line, const char* function, const char* string, ...);
AL2O3_EXTERN_C void AL2O3_WarningMsg(const char* file, int line, const char* function, const char* string, ...);
AL2O3_EXTERN_C void AL2O3_InfoMsg(const char* file, int line, const char* function, const char* string, ...);
AL2O3_EXTERN_C void AL2O3_DebugMsg(const char* file, int line, const char* function, const char* string, ...);

AL2O3_EXTERN_C void AL2O3_FailedAssert(const char* file, int line, const char* function, const char* statement);

#define ErrorMsg(str, ...) AL2O3_ErrorMsg(__LINE__, __FILE__, __FUNCTION__, str, ##__VA_ARGS__)
#define WarningMsg(str, ...) AL2O3_WarningMsg(__LINE__, __FILE__, __FUNCTION__, str, ##__VA_ARGS__)
#define InfoMsg(str, ...) AL2O3_InfoMsg(__LINE__, __FILE__, __FUNCTION__, str, ##__VA_ARGS__)

#ifndef NDEBUG

#define DebugMsg(str, ...) AL2O3_DebugMsg(__LINE__, __FILE__, __FUNCTION__, str, ##__VA_ARGS__)
#define IFASSERT(x) x
#if defined(ORBIS)
// there is a large amount of stuff included via header files ...
#define ASSERT(cond) SCE_GNM_ASSERT(cond)
#else //!ORBIS
#define ASSERT(b) if (b) {} else { AL2O3_FailedAssert(__FILE__, __LINE__, __FUNCTION__, #b); }
#endif //end !ORBIS

#else //!NDEBUG
#define DebugMsg(str, ...)
#define ASSERT(b)
#define IFASSERT(x)
#endif //end !DEBUG

#ifdef USE_LOGGING
#define LOGDEBUG(message) AL2O3_DebugMsg( __FILE__, __LINE__, __FUNCTION__, message)
#define LOGINFO(message) AL2O3_InfoMsg( __FILE__, __LINE__, __FUNCTION__, message)
#define LOGWARNING(message) AL2O3_WarningMsg( __FILE__, __LINE__, __FUNCTION__, message)
#define LOGERROR(message) AL2O3_ErrorMsg( __FILE__, __LINE__, __FUNCTION__, message)

#define LOGDEBUGF(message, ...) AL2O3_DebugMsg( __FILE__, __LINE__, __FUNCTION__, message, ##__VA_ARGS__)
#define LOGINFOF(message, ...) AL2O3_InfoMsg( __FILE__, __LINE__, __FUNCTION__, message, ##__VA_ARGS__)
#define LOGWARNINGF(message, ...) AL2O3_WarningMsg( __FILE__, __LINE__, __FUNCTION__, message, ##__VA_ARGS__)
#define LOGERRORF(message, ...) AL2O3_ErrorMsg( __FILE__, __LINE__, __FUNCTION__, message, ##__VA_ARGS__)

#else //!USE_LOGGING
#define LOGDEBUG(message) ((void)0)
#define LOGINFO(message) ((void)0)
#define LOGWARNING(message) ((void)0)
#define LOGERROR(message) ((void)0)

#define LOGDEBUGF(...) ((void)0)
#define LOGINFOF(...) ((void)0)
#define LOGWARNINGF(...) ((void)0)
#define LOGERRORF(...) ((void)0)
#endif //end !USE_LOGGING

#endif //AL2O3_PLATFORM_DEBUG_H
