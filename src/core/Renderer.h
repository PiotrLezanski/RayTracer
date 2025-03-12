#pragma once

#include "glad/glad.h"
#include "../utils/utils.h"
#include "Camera.h"
#include "../utils/Ray.h"
#include "../utils/RenderedImageSettings.h"
#include "../Scene/HittableScene.h"

#include <iostream>
#include <thread>
#include <chrono>

// It returns enum telling what needs to be regenerated.
// The rules are:
//	- do not regenerate if nothing changed
//  - regenerate renderer if only it's parameters changed
//  - regenerate all if camera settings changed, or both camera and renderer
enum RegenerationType : unsigned int
{
	RegenerateNone = 0,
	RegenerateRenderer,
	RegenerateAll
};

using RenderTime = double;

class Renderer
{
public:
	Renderer(std::shared_ptr<Camera> camera, std::unique_ptr<HittableScene> world = nullptr);

	// Main method to render
	void startRendering();
	void stopRendering();
	void rerender();

	// This method will try to override current renderer and camera settings
	// based on values set in "settings", only if given value is new.
	RegenerationType overrideSetting(const RenderedImageSettings& settings);

	RenderedImageSettings getImageSettings() const;

	const auto getTextureId() const { return m_textureId; }
	std::shared_ptr<Camera> getCamera() const { return m_camera; }
	std::shared_ptr<Image> getImage() const { return getCamera()->getImage(); }
	bool isImageRendered() const { return m_isImageRendered; }

	int getSamplesPerPixel() const { return m_samplesPerPixel; }
	void setSamplesPerPixel(int samplesPerPixel);

	int getMaxRayRecursionDepth() const { return m_maxRayRecursionDepth; }
	void setMaxRayRecursionDepth(int maxRayRecursionDepth) { m_maxRayRecursionDepth = maxRayRecursionDepth; }

	RenderTime getRenderTime() const { return m_renderTime; }

private:
	void renderRow(int32 rowIndex);

	// Return final color of given pixel
	// Antialiasing is part of this process
	// By default color will be gamma-corrected.
	const Color& calculateFinalColorAt(int i, int j, bool gammaCorrect = true);

	void initializeTexture();

	// Rendering is done is steps.
	// Every row is rendered on seperate thread (check render() and renderThread methods)
	// After row is rendered, we want to upgrade the structure.
	// This method is for that purpose and is called in rendering process.
	void updateTextureRow(int32 rowIndex);

private:
	std::shared_ptr<Camera> m_camera;
	// Scene to be rendered
	std::unique_ptr<HittableScene> m_world;

	// Count of random samples for each pixel
	// Used for antialiasing
	int m_samplesPerPixel = DEFAULT_SAMPLES_PER_PIXEL;
	double m_scale = 1.0 / m_samplesPerPixel;

	// Maximum number of ray bounces into scene
	int m_maxRayRecursionDepth = DEFAULT_MAX_RECURSION_DEPTH;

	bool m_isImageRendered = false;
	// Id of the texture made of the rendered image
	GLuint m_textureId = 0;
	bool m_stopRendering = false;
	RenderTime m_renderTime = 0.0;
};