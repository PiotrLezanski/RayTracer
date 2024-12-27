#pragma once

#include "utils.h"

// Class to store current settings of Camera and Rendered
// They can be changed through ControlsWindow
struct RenderedImageSettings
{
	Point3d cameraLookFrom = DEFAULT_CAMERA_LOOK_FROM;
	Point3d cameraLookAt = DEFAULT_CAMERA_LOOK_AT;
	float fieldOfView = DEFAULT_FIELD_OF_VIEW;
	int samplesPerPixel = DEFAULT_SAMPLES_PER_PIXEL;
	int maxRecursionDepth = DEFAULT_MAX_RECURSION_DEPTH;
};