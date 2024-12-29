#include "Camera.h"

#include "../App/App.h"

Viewport::Viewport(const Camera* camera)
	: m_camera(camera)
{
	const double imageHeight = m_camera->getImage()->height();
	const double imageWidth = m_camera->getImage()->width();

	const double theta = degreesToRadians(camera->getFieldOfView());
	const double h = std::tan(theta / 2);

	m_height = 2 * h * camera->getFocalLength();
	m_width = m_height * (imageWidth / imageHeight);

	m_upDownVec = m_height * -camera->getFrameUpVector();
	m_leftRightVec = m_width * camera->getFrameRightVector();

	m_deltaUpDown = m_upDownVec / imageHeight;
	m_deltaLeftRight = m_leftRightVec / imageWidth;

	// Calculate the location of the upper left pixel
	const auto upperLeft = camera->getCameraCenter() -
		(camera->getFocalLength() * camera->getOppositeViewDirectionVector())
		- m_upDownVec / 2.0 - m_leftRightVec / 2.0;
		
	m_startPixel = upperLeft +
		0.5 * (m_deltaUpDown + m_deltaUpDown);
}

Camera::Camera(std::shared_ptr<Image> image, Point3d lookFrom,
	Point3d lookAt, double fieldOfView)
	: m_image(image), m_lookFrom(lookFrom), 
		m_lookAt(lookAt), m_fieldOfView(fieldOfView)
{
	initialize();
}

void Camera::regenerate()
{
	initialize();
}

void Camera::initialize()
{
	m_cameraCenter = m_lookFrom;
	m_focalLength = (m_lookFrom - m_lookAt).length();

	// Initialize vectors defining camera frame
	// to take into account it's position and tilt
	m_oppositeViewDirection = unit_vector(m_lookFrom - m_lookAt);
	m_frameRightVector = unit_vector(cross_product(m_vectorUp, m_oppositeViewDirection));
	m_frameUpVector = cross_product(m_oppositeViewDirection, m_frameRightVector);

	m_viewport = std::make_unique<Viewport>(this);
}
