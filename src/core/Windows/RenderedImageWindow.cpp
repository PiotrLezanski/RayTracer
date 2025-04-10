#include "RenderedImageWindow.h"

#include "../../Scene/Hittable/HittableScene.h"
#include "../../Scene/Shapes/Sphere.h"
#include "../../Scene/Materials/AllMaterials.h"
#include "../BVH/BVH_Tree.h"

#include <vector>

namespace
{
	HittableScene createComplexScene()
	{
        HittableScene world;

        // Ground with a new color
        auto ground_material = std::make_shared<Lambertian>(Color(0.3, 0.4, 0.6));
        world.add(std::make_shared<Sphere>(Point3d(0, -1000, 0), 1000, ground_material));

        // Function to add a planet with an optional ring
        auto addPlanetWithRing = [&](Point3d center, double radius, std::shared_ptr<Material> material, bool add_ring, Color ring_color) {
            // Planet
            world.add(std::make_shared<Sphere>(center, radius, material));

            // Optional ring
            if (add_ring) {
                int ring_count = 20;
                double ring_radius = radius + 0.5;
                for (int i = 0; i < ring_count; i++) {
                    double angle = 2.0 * PI * i / ring_count;
                    Point3d ring_center = center + Point3d(ring_radius * cos(angle), 0.0, ring_radius * sin(angle));
                    auto ring_material = std::make_shared<Metal>(ring_color, 0.0);
                    world.add(std::make_shared<Sphere>(ring_center, 0.1, ring_material));
                }
            }
            };

        // Small random spheres
        for (int a = -5; a < 5; a++) {
            for (int b = -5; b < 5; b++) {
                auto choose_mat = randomDouble();
                Point3d center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

                if ((center - Point3d(4, 0.2, 0)).length() > 0.9) {
                    std::shared_ptr<Material> sphere_material;

                    if (choose_mat < 0.8) {
                        // Diffuse
                        auto albedo = randomVector() * randomVector();
                        sphere_material = std::make_shared<Lambertian>(albedo);
                        world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                    }
                    else if (choose_mat < 0.95) {
                        // Metal
                        auto albedo = randomVector(0.5, 1);
                        auto fuzz = randomDouble(0, 0.5);
                        sphere_material = std::make_shared<Metal>(albedo, fuzz);
                        world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                    }
                    else {
                        // Glass
                        sphere_material = std::make_shared<Refractive>(1.5);
                        world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                    }
                }
            }
        }

        // Planets with rings
        auto material1 = std::make_shared<Refractive>(1.5);
        addPlanetWithRing(Point3d(0, 1, 0), 1.0, material1, true, Color(0.8, 0.6, 0.2));

        auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
        addPlanetWithRing(Point3d(-4, 1, 0), 1.0, material2, true, Color(0.5, 0.5, 0.5));

        auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
        addPlanetWithRing(Point3d(4, 1, 0), 1.0, material3, false, Color(0, 0, 0));

        // Glass sphere
        auto material4 = std::make_shared<Refractive>(1.5);
        world.add(std::make_shared<Sphere>(Point3d(0, 2, 3), 0.5, material4));

        // Creates HittableScene with only one element, which is
        // BVH_Node with all objects from the scene
        world = HittableScene(std::make_shared<BVH_Tree>(world.getScene()));

        return world;
	}
}

RenderedImageWindow::RenderedImageWindow()
{
    m_image = std::make_shared<Image>(RENDERED_IMAGE_HEIGHT);
    m_camera = std::make_shared<Camera>(m_image);

    // Create Scene to be rendered
    // Scene consist of Hittable objects
    auto world = std::make_unique<HittableScene>(std::move(createComplexScene()));
    m_renderer = std::make_shared<Renderer>(m_camera, std::move(world));
}

void RenderedImageWindow::init()
{
    if (!m_renderer->isImageRendered())
    {
        // Rendered image can be retrieved from renderer
        m_renderer->startRendering();
    }

	// UI will be built here
    initImGuiFrame();
}

void RenderedImageWindow::initImGuiFrame()
{
    const int32 imageWidth = m_renderer->getImage()->width();
    const int32 imageHeight = m_renderer->getImage()->height();

    // Window cannot be made smaller than image
    const ImVec2 minSize(imageWidth, imageHeight);
    // No maximum constraint
    const ImVec2 maxSize(FLT_MAX, FLT_MAX);
    // Apply the constraints to the next window
    ImGui::SetNextWindowSizeConstraints(minSize, maxSize);

    ImGui::Begin("Rendered Image");
    ImGui::Text("Resolution: %dx%d", imageWidth, imageHeight);

    ImGui::Text("Rendering time: %.2f s", m_renderer->getRenderTime());

    // Get the available size in the ImGui window
    ImVec2 availableSize = ImGui::GetContentRegionAvail();

    // Maintain the aspect ratio of the image
    const double aspectRatio = m_renderer->getImage()->getAspectRatio();
    float width = availableSize.x;
    float height = availableSize.x / aspectRatio;

    // If the height exceeds the available vertical size, adjust width and height
    if (height > availableSize.y)
    {
        height = availableSize.y;
        width = availableSize.y * aspectRatio;
    }

    // Get rendered image texture and view it on the screen
    ImGui::Image((ImTextureID)(intptr_t)m_renderer->getTextureId(), ImVec2(width, height));

    ImGui::End();
}