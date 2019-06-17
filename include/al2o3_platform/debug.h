#pragma once
#ifndef AL2O3_PLATFORM_DEBUG_H
#define AL2O3_PLATFORM_DEBUG_H

#include "al2o3_platform/platform.h"

#ifndef USE_LOGGING
#define USE_LOGGING 1
#endif // end USE_LOGGING

// These functions are actually called, allows for transparent overriding of the log functions
// defaults to printf/outputdebugstring
typedef struct AL2O3_Logger_t {
	void (*errorMsg)(char const* file, int line, const char* function, char const* msg);
	void (*warningMsg)(char const* file, int line, const char* function, char const* msg);
	void (*infoMsg)(char const* file, int line, const char* function, char const* msg);
	void (*debugMsg)(char const* file, int line, const char* function, char const* msg);

	void (*failedAssert)(char const* file, int line, const char* function, char const* statement);
} AL2O3_Logger_t;
AL2O3_EXTERN_C AL2O3_Logger_t AL2O3_Logger;

// lowest level debug output
AL2O3_EXTERN_C void AL2O3_OutputDebug(char const *msg);

// call the functions in the global logger function 
AL2O3_EXTERN_C void AL2O3_ErrorMsg(const char* file, int line, const char* function, const char* string, ...);
AL2O3_EXTERN_C void AL2O3_WarningMsg(const char* file, int line, const char* function, const char* string, ...);
AL2O3_EXTERN_C void AL2O3_InfoMsg(const char* file, int line, const char* function, const char* string, ...);
AL2O3_EXTERN_C void AL2O3_DebugMsg(const char* file, int line, const char* function, const char* string, ...);
AL2O3_EXTERN_C void AL2O3_FailedAssert(const char* file, int line, const char* function, const char* statement);

#ifndef NDEBUG
#if defined(ORBIS)
// there is a large amount of stuff included via header files ...
#define ASSERT(cond) SCE_GNM_ASSERT(cond)
#else //!ORBIS
#define ASSERT(b) { if(!(b)) { AL2O3_FailedAssert(__FILE__, __LINE__, __FUNCTION__, #b); } }
#endif //end !ORBIS
#else //!NDEBUG
#define ASSERT(b)
#endif //end !DEBUG

#ifdef USE_LOGGING
#ifndef NDEBUG
#define LOGDEBUG(message) AL2O3_DebugMsg( __FILE__, __LINE__, __FUNCTION__, message)
#define LOGDEBUGF(message, ...) AL2O3_DebugMsg( __FILE__, __LINE__, __FUNCTION__, message, ##__VA_ARGS__)
#else
#define LOGDEBUG(message) ((void)0)
#define LOGDEBUGF(message, ...) ((void)0)
#endif // end NDEBUG

#define LOGINFO(message) AL2O3_InfoMsg( __FILE__, __LINE__, __FUNCTION__, message)
#define LOGINFOF(message, ...) AL2O3_InfoMsg( __FILE__, __LINE__, __FUNCTION__, message, ##__VA_ARGS__)

#define LOGWARNING(message) AL2O3_WarningMsg( __FILE__, __LINE__, __FUNCTION__, message)
#define LOGWARNINGF(message, ...) AL2O3_WarningMsg( __FILE__, __LINE__, __FUNCTION__, message, ##__VA_ARGS__)

#define LOGERROR(message) AL2O3_ErrorMsg( __FILE__, __LINE__, __FUNCTION__, message)
#define LOGERRORF(message, ...) AL2O3_ErrorMsg( __FILE__, __LINE__, __FUNCTION__, message, ##__VA_ARGS__)

#else //!USE_LOGGING

#define LOGDEBUG(message) ((void)0)
#define LOGINFO(message) ((void)0)
#define LOGWARNING(message) ((void)0)
#define LOGERROR(message) ((void)0)

#define LOGDEBUGF(message, ...) ((void)0)
#define LOGINFOF(message, ...) ((void)0)
#define LOGWARNINGF(message, ...) ((void)0)
#define LOGERRORF(message, ...) ((void)0)

#endif //end !USE_LOGGING

#endif //AL2O3_PLATFORM_DEBUG_H
