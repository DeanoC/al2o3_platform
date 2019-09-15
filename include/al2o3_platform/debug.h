#pragma once

/// provide 4 logging calls LOGDEBUG, LOGINFO, LOGWARNING, LOGERROR
/// all can be hooked easily by log managers and will effect all libraries and apps
/// easily. Can be removed completely by defined USE_LOGGING 0 globally
/// LOGDEBUG is only used in debug builds and removed in release
/// each is a varargs using printf like formatting, there is a total limit per
/// message of 64 KB per post-formatted string
/// Addition a very low level AL2O3_OutputDebug is always available and will
/// output a message (no arguments) useful for whe USE_LOGGING is off

#include "al2o3_platform/platform.h"
#include <assert.h> // for assert

#ifndef USE_LOGGING
#define USE_LOGGING 1
#endif // end USE_LOGGING

// These functions are actually called, allows for transparent overriding of the log functions
// defaults to outputdebug
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
#define ASSERT(b) { if(!(b)) { AL2O3_FailedAssert(__FILE__, __LINE__, __FUNCTION__, #b); assert((b)); } }
#else //!NDEBUG
#define ASSERT(b)
#endif //end !DEBUG

#ifdef USE_LOGGING
#ifndef NDEBUG
#define LOGDEBUG(message, ...) AL2O3_DebugMsg( __FILE__, __LINE__, __FUNCTION__, message, ##__VA_ARGS__)
#else
#define LOGDEBUG(message, ...) ((void)0)
#endif // end NDEBUG

#define LOGINFO(message, ...) AL2O3_InfoMsg( __FILE__, __LINE__, __FUNCTION__, message, ##__VA_ARGS__)
#define LOGWARNING(message, ...) AL2O3_WarningMsg( __FILE__, __LINE__, __FUNCTION__, message, ##__VA_ARGS__)
#define LOGERROR(message, ...) AL2O3_ErrorMsg( __FILE__, __LINE__, __FUNCTION__, message, ##__VA_ARGS__)

#else //!USE_LOGGING

#define LOGDEBUG(message, ...) ((void)0)
#define LOGINFO(message, ...) ((void)0)
#define LOGWARNING(message, ...) ((void)0)
#define LOGERROR(message, ...) ((void)0)

#endif //end !USE_LOGGING
