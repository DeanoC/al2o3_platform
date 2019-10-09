#pragma once

/// Visual debug are primitives that can be rendered onto a screen
/// By default they do nothing, but if the application has a
/// renderer, they are expected to be hooked and rendered.
/// Having a very low level interface allows no coupling between being able to
/// display basic visual debugging information and any actual renderer.

// the single colour solid primitives with a colour of 0 will generate a per primitive
// colour from a internal table, that should make each face visible

#include "al2o3_platform/platform.h"

#ifndef USE_VISUAL_DEBUGGING
#define USE_VISUAL_DEBUGGING 1
#endif // end USE_VISUAL_DEBUGGING

// These functions are actually called, allows for transparent overriding
// defaults to logging
typedef struct AL2O3_VisualDebugging_t {

	void (*Line)(float p0x, float p0y, float p0z, float p1x, float p1y, float p1z, uint32_t colour);
	void (*Lines)(uint32_t lineCount, float const * verts, uint32_t colour);

	void (*LineStrip)(uint32_t lineCount, float const * verts, uint32_t colour);
	void (*SolidTris)(uint32_t triCount, float const * verts, uint32_t colour);
	void (*SolidQuads)(uint32_t quadCount, float const * verts, uint32_t colour);

	// euler rotation are in radians
	void (*Tetrahedron)(float const* pos, float const* eulerRots, float const* scale, uint32_t colour);
	void (*Cube)(float const* pos, float const* eulerRots, float const* scale, uint32_t colour);
	void (*Octahedron)(float const* pos, float const* eulerRots, float const* scale, uint32_t colour);
	void (*Icosahedron)(float const* pos, float const* eulerRots, float const* scale, uint32_t colour);
	void (*Dodecahedron)(float const* pos, float const* eulerRots, float const* scale, uint32_t colour);

} AL2O3_VisualDebugging_t;
AL2O3_EXTERN_C AL2O3_VisualDebugging_t AL2O3_VisualDebugging;

#define VISDEBUG_PACKCOLOUR(r, g, b, a) (((uint32_t)r) << 0) | ((g) << 8) | ((b) << 16) | ((a) << 24)

#ifdef USE_VISUAL_DEBUGGING

#define VISDEBUG_LINE(p0x, p0y, p0z, p1x, p1y, p1z, packedcolor) \
  AL2O3_VisualDebugging.Line(p0x, p0y, p0z,  p1x, p1y, p1z, packedcolor)
#define VISDEBUG_SOLID_TRI(p0x, p0y, p0z, p1x, p1y, p1z, p2x, p2y, p2z, packedcolor) \
	AL2O3_VisualDebugging.SolidTri(p0x, p0y, p0z,  p1x, p1y, p1z, p2x, p2y, p2z, packedcolor)

#define VISDEBUG_LINES(lineCount, verts, packedcolor) \
  AL2O3_VisualDebugging.Lines(lineCount, verts, packedcolor)
#define VISDEBUG_LINESTRIP(lineCount, verts, packedcolor) \
  AL2O3_VisualDebugging.LineStrip(lineCount, verts, packedcolor)

#define VISDEBUG_SOLID_TRIS(triCount, verts, packedcolor) \
  AL2O3_VisualDebugging.SolidTris(triCount, verts, packedcolor)
#define VISDEBUG_SOLID_QUADS(quadCount, verts, packedcolor) \
  AL2O3_VisualDebugging.SolidQuads(quadCount, verts, packedcolor)

#define VISDEBUG_TETRAHEDRON(pos, rot, scale, packedcolor) \
  AL2O3_VisualDebugging.Tetrahedron(pos, rot, scale, packedcolor)

#define VISDEBUG_CUBE(pos, rot, scale, packedcolor) \
  AL2O3_VisualDebugging.Cube(pos, rot, scale, packedcolor)

#define VISDEBUG_OCTAHEDRON(pos, rot, scale, packedcolor) \
  AL2O3_VisualDebugging.Octahedron(pos, rot, scale, packedcolor)

#define VISDEBUG_ICOSAHEDRON(pos, rot, scale, packedcolor) \
  AL2O3_VisualDebugging.Icosahedron(pos, rot, scale, packedcolor)

#define VISDEBUG_DODECAHEDRON(pos, rot, scale, packedcolor) \
  AL2O3_VisualDebugging.Dodecahedron(pos, rot, scale, packedcolor)

#else

#define VISDEBUG_LINE(p0x, p0y, p0z, p1x, p1y, p1z, packedcolor) ((void)0)
#define VISDEBUG_SOLID_TRI(p0x, p0y, p0z, p1x, p1y, p1z, p2x, p2y, p2z, packedcolor) ((void)0)

#define VISDEBUG_LINES(lineCount, verts, packedcolor) ((void)0)
#define VISDEBUG_LINESTRIP(lineCount, verts, packedcolor) ((void)0)

#define VISDEBUG_SOLID_TRIS(triCount, verts, packedcolor) ((void)0)
#define VISDEBUG_SOLID_QUADS(quadCount, verts, packedcolor) ((void)0)

#define VISDEBUG_TETRAHEDRON(pos, rot, scale, packedcolor) ((void)0)
#define VISDEBUG_CUBE(pos, rot, scale, packedcolor) ((void)0)
#define VISDEBUG_OCTAHEDRON(pos, rot, scale, packedcolor) ((void)0)
#define VISDEBUG_ICOSAHEDRON(pos, rot, scale, packedcolor) ((void)0)
#define VISDEBUG_DODECAHEDRON(pos, rot, scale, packedcolor) ((void)0)

#endif