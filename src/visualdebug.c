#include "al2o3_platform/platform.h"
#include "al2o3_platform/debug.h"
#include "al2o3_platform/visualdebug.h"

static void Line(float p0x, float p0y, float p0z, float p1x, float p1y, float p1z, uint32_t colour) {}
static void Lines(uint32_t lineCount, float const * verts, uint32_t colour) {}
static void LineStrip(uint32_t lineCount, float const * verts, uint32_t colour) {}
static void SolidTris(uint32_t triCount, float const * verts, uint32_t colour) {}
static void SolidQuads(uint32_t quadCount, float const * verts, uint32_t colour) {}
static void Tetrahedron(float const* pos, float const* eulerRots, float const* scale, uint32_t colour) {}
static void Cube(float const* pos, float const* eulerRots, float const* scale, uint32_t colour) {}


AL2O3_EXTERN_C AL2O3_VisualDebugging_t AL2O3_VisualDebugging = {
		&Line,
		&Lines,
		&LineStrip,
		&SolidTris,
		&SolidQuads,
		&Tetrahedron,
		&Cube,
};



