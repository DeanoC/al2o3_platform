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

	void (*Line)(float p0x, float p0y, float p0z, float p1x, float p1y, float p1z, uint32_t colour);

} AL2O3_VisualDebugging_t;
AL2O3_EXTERN_C AL2O3_VisualDebugging_t AL2O3_VisualDebugging;

#define VISDEBUG_PACKCOLOUR(r, g, b, a) ((r) << 24) | ((g) << 16) | ((b) << 8) | ((a) << 0)

#ifdef USE_VISUAL_DEBUGGING
#define VISDEBUG_LINE(p0x, p0y, p0z, p1x, p1y, p1z, packedcolor) \
  AL2O3_VisualDebugging.Line(p0x, p0y, p0z,  p1x, p1y, p1z, packedcolor)
#else
#define VISDEBUG_LINE(p0, p1, colour) ((void)0)
#endif