#include "al2o3_platform/platform.h"
#include "al2o3_platform/debug.h"
#include "al2o3_platform/visualdebug.h"

static void LineLog(float p0[3], float p1[3], float colour[4]) {
	LOGINFO("Line from <%1.2f, %1.2f, %1.2f> to "
					"<%1.2f, %1.2f, %1.2f> of "
					"<%1.2f, %1.2f, %1.2f,%1.2>",
					p0[0], p0[1], p0[2],
					p1[0], p1[1], p1[2],
					colour[0], colour[1], colour[2], colour[3]);
}

AL2O3_EXTERN_C AL2O3_VisualDebugging_t AL2O3_VisualDebugging = {
		&LineLog,
};



