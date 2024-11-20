#include "Renderer.h"

using Color = Vec3<double>;

Renderer::Renderer(std::shared_ptr<Camera> camera)
	: m_camera(camera)
{

}

void Renderer::render()
{
    if (m_isImageRendered)
        return;

    std::shared_ptr<Image> image = getImage();
    std::shared_ptr<Viewport> viewport = getCamera()->getViewport();
    // Image
    int32 image_width = image->width();
    int32 image_height = image->height();

    // Render
    for (int32 i = 0; i < image_height; i++)
    {
        std::clog << "\rScanlines remaining: " << (image_height - i) << ' ' << std::flush;
        for (int32 j = 0; j < image_width; j++)
        {
            const Point3d& pixelCenter = viewport->getStartPixel() +
                ((double)i * viewport->getUpDownDeltaVec()) +
                ((double)j * viewport->getLeftRightDeltaVec());

            const Point3d& cameraCenter = getCamera()->getCameraCenter();
            const Vec& rayDirection = pixelCenter - cameraCenter;

            const Ray ray(cameraCenter, rayDirection);
            const Color& pixelColor = ray.calculateColor();

            image->setColorAt(i, j, pixelColor);
        }
    }
    std::clog << "\rDone.                 \n";

    m_isImageRendered = true;
    image->printImagePPM(std::cout);
}