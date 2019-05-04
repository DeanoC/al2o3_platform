#include "al2o3_platform/platform.h"

#include <stdio.h> // for sprintf family
#include <stdarg.h> // for va_xxx functions

#if PLATFORM != PLATFORM_WINDOWS
void AL2O3_OutputDebug(char const* msg)
{
		printf("%s", msg);
}
#else

#include "al2o3_platform/windows.h"
void AL2O3_OutputDebug(char const *msg) {
	OutputDebugString(msg);
}
#endif

#define MSG_MAX 2048

static void errorMsg(char const *file, int line, const char *function, char const *msg) {
	char out[MSG_MAX];
	sprintf(out, "%s(%i): ERR (%s) - %s\n", file, line, function, msg);
	AL2O3_OutputDebug(out);
}

static void warningMsg(char const *file, int line, const char *function, char const *msg) {
	char out[MSG_MAX];
	sprintf(out, "%s(%i): WARN (%s) - %s\n", file, line, function, msg);
	AL2O3_OutputDebug(out);
}

static void infoMsg(char const *file, int line, const char *function, char const *msg) {
	char out[MSG_MAX];
	sprintf(out, "%s(%i): INFO (%s) - %s\n", file, line, function, msg);
	AL2O3_OutputDebug(out);
}

static void debugMsg(char const *file, int line, const char *function, char const *msg) {
	char out[MSG_MAX];
	sprintf(out, "%s(%i): DBG (%s) - %s\n", file, line, function, msg);
	AL2O3_OutputDebug(out);
}

static void failedAssert(char const *file, int line, char const *msg) {
	char out[MSG_MAX];
	sprintf(out, "%s(%i): Assert Failed - %s\n", file, line, msg);
	AL2O3_OutputDebug(out);
}

AL2O3_EXTERN_C void AL2O3_ErrorMsg(const char *file, int line, const char *function, const char *string, ...) {
	va_list arglist;

	char out[MSG_MAX];
	va_start(arglist, string);
	vsprintf(out, string, arglist);
	va_end(arglist);

	AL2O3_Log.errorMsg(file, line, function, out);
}

AL2O3_EXTERN_C void AL2O3_WarningMsg(const char *file, int line, const char *function, const char *string, ...) {
	va_list arglist;

	char out[MSG_MAX];
	va_start(arglist, string);
	vsprintf(out, string, arglist);
	va_end(arglist);

	AL2O3_Log.warningMsg(file, line, function, out);
}

AL2O3_EXTERN_C void AL2O3_InfoMsg(const char *file, int line, const char *function, const char *string, ...) {
	va_list arglist;

	char out[MSG_MAX];
	va_start(arglist, string);
	vsprintf(out, string, arglist);
	va_end(arglist);

	AL2O3_Log.infoMsg(file, line, function, out);
}

AL2O3_EXTERN_C void AL2O3_DebugMsg(const char *file, int line, const char *function, const char *string, ...) {
#ifdef NDEBUG
	AL2O3_Log.warningMsg(file, line, function, "DebugMsg called in a non-debug version")
#else
	va_list arglist;

	char out[MSG_MAX];
	va_start(arglist, string);
	vsprintf(out, string, arglist);
	va_end(arglist);

	AL2O3_Log.debugMsg(file, line, function, out);
#endif
}

AL2O3_EXTERN_C void AL2O3_FailedAssert(const char *file, int line, const char *statement) {
	AL2O3_Log.failedAssert(file, line, statement);
}

AL2O3_EXTERN_C AL2O3_Logger AL2O3_Log = {
		&errorMsg,
		&warningMsg,
		&infoMsg,
		&debugMsg,
		&failedAssert
};

