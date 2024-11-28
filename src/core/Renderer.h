#pragma once

#include "../utils/utils.h"
#include "Camera.h"
#include "../utils/Ray.h"
#include "../Scene/HittableScene.h"

#include <iostream>

class Renderer
{
public:
	explicit Renderer(std::shared_ptr<Camera> camera);
	void render(const HittableScene& world);

	std::shared_ptr<Camera> getCamera() const { return m_camera; }
	std::shared_ptr<Image> getImage() const { return getCamera()->getImage(); }

private:
	// Return final color of given pixel
	// Antialiasing is part of this process
	const Color& calculateFinalColorAt(const HittableScene& world, int i, int j);

private:
	std::shared_ptr<Camera> m_camera;
	bool m_isImageRendered = false;

	// Count of random samples for each pixel
	// Used for antialiasing
	const int m_samplesPerPixel = 10;
	const double m_scale = 1.0 / m_samplesPerPixel;
};