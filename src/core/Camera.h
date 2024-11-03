#pragma once

#include "../utils/utils.h"
#include "Image.h"

class Camera;

// virtual rectangle in the 3D world that contains
// grid of image pixel locations
struct Viewport
{
public:
	Viewport(const Camera* camera);
	Vec getUpDownDeltaVec() const { return m_deltaUpDown; }
	Vec getLeftRightDeltaVec() const { return m_deltaLeftRight; }
	Point3d getStartPixel() const { return m_startPixel; }

private:
	const Camera* m_camera;

	double m_height = 2.0;
	double m_width;

	// vectors to help navigate through Viewport grid
	// We will scan image from uper left pixel, then left to right for every row
	Vec m_upDownVec;
	Vec m_leftRightVec;

	// distances between horizontal and vertical pixels in Viewport grid
	Vec m_deltaUpDown;
	Vec m_deltaLeftRight;

	// upper left pixel
	Point3d m_startPixel;
};

class Camera
{
public:
	Camera(std::shared_ptr<Image> image);

	std::shared_ptr<Image> getImage() const { return m_image; }
	std::shared_ptr<Viewport> getViewport() const { return m_viewport; }
	Point3d getCameraCenter() const { return m_cameraCenter; }
	double getFocalLength() const { return m_focalLength; }
private:
	std::shared_ptr<Image> m_image;
	std::shared_ptr<Viewport> m_viewport;

	// point from 3D from which all scene rays will originate
	Point3d m_cameraCenter = Point3d(0, 0, 0);

	// distance between camera na viewport
	double m_focalLength = 1.0;
};