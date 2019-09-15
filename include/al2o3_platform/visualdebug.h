#pragma once

/// Visual debug are primitives that can be rendered onto a screen
/// By default that just log the parameters, but if the application has a
/// renderer, they are expected to be hooked and rendered.
/// Having a very low level interface allows no coupling between being able to
/// display basic visual debugging information and any actual renderer.

#include "al2o3_platform/platform.h"

#ifndef USE_VISUAL_DEBUGGING
#define USE_VISUAL_DEBUGGING 1
#endif // end USE_VISUAL_DEBUGGING

// These functions are actually called, allows for transparent overriding
// defaults to logging
typedef struct AL2O3_VisualDebugging_t {

	void (*Line)(float p0[3], float p1[3], float colour[4]);

} AL2O3_VisualDebugging_t;
AL2O3_EXTERN_C AL2O3_VisualDebugging_t AL2O3_VisualDebugging;

#ifdef USE_VISUAL_DEBUGGING
#define VISDEBUG_LINE(p0, p1, colour) AL2O3_VisualDebugging->Line(p0, p1, colour)
#else
#define VISDEBUG_LINE(p0, p1, colour) ((void)0)
#endif