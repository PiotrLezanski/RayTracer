#include "RenderedImageWindow.h"

#include "glad/glad.h"
#include "imgui.h"
#include "imgui_impl_opengl3_loader.h"
#include <GLFW/glfw3.h>

#include <vector>


RenderedImageWindow::RenderedImageWindow()
{
    m_image = std::make_shared<Image>(256);
    m_camera = std::make_shared<Camera>(m_image);
    m_renderer = std::make_shared<Renderer>(m_camera);
}

void RenderedImageWindow::init()
{
	// UI will be built here
    m_renderer->render();
}