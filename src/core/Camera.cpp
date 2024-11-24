#include "Camera.h"

Viewport::Viewport(const Camera* camera)
	: m_camera(camera)
{
	const double imageHeight = m_camera->getImage()->height();
	const double imageWidth = m_camera->getImage()->width();
	m_width = m_height * (imageWidth / imageHeight);

	m_upDownVec = Vec3(0.0, -m_height, 0.0);
	m_leftRightVec = Vec3(m_width, 0.0, 0.0);

	m_deltaUpDown = m_upDownVec / imageHeight;
	m_deltaLeftRight = m_leftRightVec / imageWidth;

	// Calculate the location of the upper left pixel
	auto upperLeft = camera->getCameraCenter() -
		Vec(0, 0, camera->getFocalLength()) -
		m_upDownVec / 2.0 - m_leftRightVec / 2.0;
	m_startPixel = upperLeft +
		0.5 * (m_deltaUpDown + m_deltaUpDown);
}

Camera::Camera(std::shared_ptr<Image> image)
	: m_image(image)
{
	m_viewport = std::make_unique<Viewport>(this);
}