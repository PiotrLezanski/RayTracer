#pragma once

#include "glad/glad.h"
#include "../utils/utils.h"
#include "Camera.h"
#include "../utils/Ray.h"
#include "../Scene/HittableScene.h"

#include <iostream>
#include <thread>
#include <mutex>

class Renderer
{
public:
	explicit Renderer(std::shared_ptr<Camera> camera);

	// Main method to render
	void startRendering(const HittableScene& world);

	void stopRendering();

	const auto getTextureId() const { return m_textureId; }
	std::shared_ptr<Camera> getCamera() const { return m_camera; }
	std::shared_ptr<Image> getImage() const { return getCamera()->getImage(); }
	bool isImageRendered() const { return m_isImageRendered; }
	std::thread& getRenderingThread() { return m_renderingThread; }

private:
	void renderRow(const HittableScene& world, int32 rowIndex);

	// Return final color of given pixel
	// Antialiasing is part of this process
	// By default color will be gamma-corrected.
	const Color& calculateFinalColorAt(const HittableScene& world, int i, int j, bool gammaCorrect = true);

	void initializeTexture();

	// Rendering is done is steps.
	// Every row is rendered on seperate thread (check render() and renderThread methods)
	// After row is rendered, we want to upgrade the structure.
	// This method is for that purpose and is called in rendering process.
	void updateTextureRow(int32 rowIndex);

private:
	std::shared_ptr<Camera> m_camera;

	// Count of random samples for each pixel
	// Used for antialiasing
	const int m_samplesPerPixel = 10;
	const double m_scale = 1.0 / m_samplesPerPixel;

	// Maximum number of ray bounces into scene
	int m_maxRayRecursionDepth = 10;

	bool m_isImageRendered = false;
	// Id of the texture made of the rendered image
	GLuint m_textureId = 0;
	std::thread m_renderingThread;
	bool m_stopRendering = false;
};