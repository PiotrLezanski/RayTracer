#pragma once

#include <memory>

#include "../core/Camera.h"
#include "../core/Image.h"
#include "../core/Renderer.h"
#include "../core/Windows/WindowsBuilder.h"

class MainUI
{
public:
	MainUI();

	void init();

private:
	void initializeGLFW();
	void setupOpenGL();
	void initializeWindow();
	void setupImGuiContext();
	void setupUI();
	void buildUI();
	void cleanup();

private:
	std::shared_ptr<Image> m_image;
	std::shared_ptr<Camera> m_camera;
	std::shared_ptr<Renderer> m_renderer;

	GLFWwindow* m_mainWindow = nullptr;
	std::unique_ptr<WindowsBuilder> m_windowsBuilder;
};
