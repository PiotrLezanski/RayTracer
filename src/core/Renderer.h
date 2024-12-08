#pragma once

#include "glad/glad.h"
#include "../utils/utils.h"
#include "Camera.h"
#include "../utils/Ray.h"
#include "../Scene/HittableScene.h"

#include <iostream>

class Renderer
{
public:
	explicit Renderer(std::shared_ptr<Camera> camera);

	// Main method to render 
	void render(const HittableScene& world);

	// If image is rendered, create ImGui texture from it
	// It is used to view it in ImGui window
	GLuint createTextureFromImage() const;

	std::shared_ptr<Camera> getCamera() const { return m_camera; }
	std::shared_ptr<Image> getImage() const { return getCamera()->getImage(); }
	bool isImageRendered() const { return m_isImageRendered; }

private:
	// Return final color of given pixel
	// Antialiasing is part of this process
	// By default color will be gamma-corrected.
	const Color& calculateFinalColorAt(const HittableScene& world, int i, int j, bool gammaCorrect = true);

private:
	std::shared_ptr<Camera> m_camera;
	bool m_isImageRendered = false;

	// Count of random samples for each pixel
	// Used for antialiasing
	const int m_samplesPerPixel = 10;
	const double m_scale = 1.0 / m_samplesPerPixel;

	// Maximum number of ray bounces into scene
	int m_maxRayRecursionDepth = 20;
};