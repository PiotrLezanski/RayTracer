#include "RenderedImageWindow.h"

//#include "glad/glad.h"
//#include "imgui.h"
//#include "imgui_impl_opengl3_loader.h"
//#include <GLFW/glfw3.h>

#include "../../Scene/HittableScene.h"
#include "../../Scene/Shapes/Sphere.h"
#include "../../Scene/Materials/AllMaterials.h"

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
    const auto& materialGround = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    const auto& materialCenter = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    const auto& materialLeft = std::make_shared<Metal>(Color(0.8, 0.8, 0.8));
    const auto& materialRight = std::make_shared<Metal>(Color(0.8, 0.6, 0.2));

    world.add(std::make_shared<Sphere>(Point3d(0.0, -100.5, -1.0), 100.0, materialGround));
    world.add(std::make_shared<Sphere>(Point3d(0.0, 0.0, -1.2), 0.5, materialCenter));
    world.add(std::make_shared<Sphere>(Point3d(-1.0, 0.0, -1.0), 0.5, materialLeft));
    world.add(std::make_shared<Sphere>(Point3d(1.0, 0.0, -1.0), 0.5, materialRight));

	// UI will be built here

    // Render Scene
    m_renderer->render(world);
}