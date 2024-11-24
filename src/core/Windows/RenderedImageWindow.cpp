#include "RenderedImageWindow.h"

#include "glad/glad.h"
#include "imgui.h"
#include "imgui_impl_opengl3_loader.h"
#include <GLFW/glfw3.h>

#include "../../Scene/HittableScene.h"
#include "../../Scene/Shapes/Sphere.h"

#include <vector>


RenderedImageWindow::RenderedImageWindow()
{
    m_image = std::make_shared<Image>(256);
    m_camera = std::make_shared<Camera>(m_image);
    m_renderer = std::make_shared<Renderer>(m_camera);
}

void RenderedImageWindow::init()
{
    // Create Scene to be rendered
    // Scene consist of Hittable objects
    HittableScene world;
    world.add(std::make_shared<Sphere>(Point3d(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(Point3d(0, -100.5, -1), 100));

	// UI will be built here

    // Render Scene
    m_renderer->render(world);
}