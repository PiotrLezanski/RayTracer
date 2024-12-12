#include "RenderedImageWindow.h"

#include "../../Scene/HittableScene.h"
#include "../../Scene/Shapes/Sphere.h"
#include "../../Scene/Materials/AllMaterials.h"

#include <vector>

namespace
{
	HittableScene createMainScene()
	{
        HittableScene world;
        auto materialGround = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
        auto materialCenter = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
        auto materialLeft = std::make_shared<Refractive>(1.50);
        auto materialBubble = std::make_shared<Refractive>(1.00 / 1.50);
        auto materialRight = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

        world.add(std::make_shared<Sphere>(Point3d(0.0, -100.5, -1.0), 100.0, materialGround));
        world.add(std::make_shared<Sphere>(Point3d(0.0, 0.0, -1.2), 0.5, materialCenter));
        world.add(std::make_shared<Sphere>(Point3d(-1.0, 0.0, -1.0), 0.5, materialLeft));
        world.add(std::make_shared<Sphere>(Point3d(-1.0, 0.0, -1.0), 0.4, materialBubble));
        world.add(std::make_shared<Sphere>(Point3d(1.0, 0.0, -1.0), 0.5, materialRight));

        return world;
	}
}

RenderedImageWindow::RenderedImageWindow()
{
    m_image = std::make_shared<Image>(RENDERED_IMAGE_HEIGHT);
    m_camera = std::make_shared<Camera>(m_image);
    m_renderer = std::make_shared<Renderer>(m_camera);
}

void RenderedImageWindow::init()
{
    // Create Scene to be rendered
    // Scene consist of Hittable objects
    HittableScene world = std::move(createMainScene());

    // Rendered image can be retrieved from renderer
    m_renderer->render(world);

	// UI will be built here
    initImGuiFrame();
}

void RenderedImageWindow::initImGuiFrame()
{
    const int32 imageWidth = m_renderer->getImage()->width();
    const int32 imageHeight = m_renderer->getImage()->height();

    // Window cannot be made smaller than image
    ImVec2 minSize(imageWidth, imageHeight);
    // No maximum constraint
    ImVec2 maxSize(FLT_MAX, FLT_MAX);
    // Apply the constraints to the next window
    ImGui::SetNextWindowSizeConstraints(minSize, maxSize);

    ImGui::Begin("Rendered Image");
    ImGui::Text("Resolution: %dx%d", imageWidth, imageHeight);

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
    const auto textureId = m_renderer->createTextureFromImage();
    ImGui::Image((ImTextureID)(intptr_t)textureId, ImVec2(width, height));

    ImGui::End();
}