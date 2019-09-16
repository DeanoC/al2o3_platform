#include "al2o3_platform/platform.h"
#include "al2o3_platform/debug.h"
#include "al2o3_platform/visualdebug.h"

static void LineLog(float p0x, float p0y, float p0z, float p1x, float p1y, float p1z, uint32_t colour) {

	LOGINFO("Line from <%1.2f, %1.2f, %1.2f> to "
					"<%1.2f, %1.2f, %1.2f> of "
					"0x%x",
					p0x, p0y, p0z,
					p1x, p1y, p1z,
					colour);
}

AL2O3_EXTERN_C AL2O3_VisualDebugging_t AL2O3_VisualDebugging = {
		&LineLog,
};



