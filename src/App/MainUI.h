#pragma once

#include <memory>

#include "../core/Image.h"
#include "../core/Camera.h"
#include "../core/Renderer.h"
#include "GLFW/glfw3.h"

class MainUI
{
public:
	MainUI(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera,
		std::shared_ptr<Renderer> renderer);

	void init();

private:
	void initializeGLFW();
	void initializeWindow();
	void setupOpenGL();
	void setupImGuiContext();
	void setupUI();
	void buildUI();
	void cleanup();

private:
	std::shared_ptr<Image> m_image;
	std::shared_ptr<Camera> m_camera;
	std::shared_ptr<Renderer> m_renderer;

	GLFWwindow* m_window;
};
