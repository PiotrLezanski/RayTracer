#include "Renderer.h"

using Color = Vec3<double>;

Renderer::Renderer(std::shared_ptr<Camera> camera)
	: m_camera(camera)
{

}

void Renderer::render()
{
    std::shared_ptr<Image> image = m_camera->getImage();
    // Image
    int32 image_width = image->width();
    int32 image_height = image->height();

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for (int32 i = 0; i < image_height; i++)
    {
        std::clog << "\rScanlines remaining: " << (image_height - i) << ' ' << std::flush;
        std::shared_ptr<Viewport> viewport = getCamera()->getViewport();
        for (int32 j = 0; j < image_width; j++)
        {
            const Point3d& pixelCenter = viewport->getStartPixel() +
                ((double)i * viewport->getUpDownDeltaVec()) +
                ((double)j * viewport->getLeftRightDeltaVec());

            const Point3d& cameraCenter = getCamera()->getCameraCenter();
            const Vec& rayDirection = pixelCenter - cameraCenter;

            Ray ray(cameraCenter, rayDirection);
            const Color& pixelColor = ray.calculateColor();

            ColorUtils::printColor(std::cout, pixelColor);
        }
    }
    std::clog << "\rDone.                 \n";
}