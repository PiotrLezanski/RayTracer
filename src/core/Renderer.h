#pragma once
#include <iostream>

#include "../utils/utils.h"
#include "Camera.h"
#include "../utils/Ray.h"

class Renderer
{
public:
	explicit Renderer(std::shared_ptr<Camera> camera);
	void render();

	std::shared_ptr<Camera> getCamera() const { return m_camera; }
	std::shared_ptr<Image> getImage() const { return getCamera()->getImage(); }

private:
	std::shared_ptr<Camera> m_camera;
	bool m_isImageRendered = false;
};