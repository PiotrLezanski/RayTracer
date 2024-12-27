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

	double m_height;
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
	Camera(std::shared_ptr<Image> image, Point3d lookFrom = DEFAULT_CAMERA_LOOK_FROM, 
		Point3d lookAt = DEFAULT_CAMERA_LOOK_AT, double fieldOfView = DEFAULT_FIELD_OF_VIEW);

	std::shared_ptr<Image> getImage() const { return m_image; }
	std::shared_ptr<Viewport> getViewport() const { return m_viewport; }
	Point3d getCameraCenter() const { return m_cameraCenter; }
	double getFocalLength() const { return m_focalLength; }

	double getFieldOfView() const { return m_fieldOfView; }
	void setFieldOfView(double fieldOfView) { m_fieldOfView = fieldOfView; }

	const Point3d& getLookFrom() const { return m_lookFrom; }
	void setLookFrom(const Point3d&& lookFrom) { m_lookFrom = lookFrom; }

	const Point3d& getLookAt() const { return m_lookAt; }
	void setLookAt(const Point3d&& lookAt) { m_lookAt = lookAt; }

	Vec getFrameRightVector() const { return m_frameRightVector; }
	Vec getFrameUpVector() const { return m_frameUpVector; }
	Vec getOppositeViewDirectionVector() const { return m_oppositeViewDirection; }

private:
	std::shared_ptr<Image> m_image;
	std::shared_ptr<Viewport> m_viewport;

	// point from 3D from which all scene rays will originate
	Point3d m_cameraCenter = Point3d(0, 0, 0);

	// distance between camera na viewport
	double m_focalLength = 1.0;

	double m_fieldOfView;

	// We use this vector to project it onto camera plane
	// and get camera relative up vector.
	Vec m_vectorUp = Vec(0, 1, 0);
	// Point camera is looking from
	Point3d m_lookFrom;
	// Point camera is looking at
	Point3d m_lookAt;

	// Unit vectors to define camera frame (relative to camera)
	Vec m_frameRightVector;
	Vec m_frameUpVector;
	Vec m_oppositeViewDirection;
};