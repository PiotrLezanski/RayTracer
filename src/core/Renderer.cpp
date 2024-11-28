#include "Renderer.h"

namespace
{
    Vec sampleSquare()
	{
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square
        return Vec(randomDouble() - 0.5, randomDouble() - 0.5, 0);
    }
}

Renderer::Renderer(std::shared_ptr<Camera> camera)
	: m_camera(camera)
{

}

void Renderer::render(const HittableScene& world)
{
    if (m_isImageRendered)
        return;

    std::shared_ptr<Image> image = getImage();

    // Image
    int32 image_width = image->width();
    int32 image_height = image->height();

    // Render
    for (int32 i = 0; i < image_height; i++)
    {
        std::clog << "\rScanlines remaining: " << (image_height - i) << ' ' << std::flush;
        for (int32 j = 0; j < image_width; j++)
        {
            const Color& pixelColor = calculateFinalColorAt(world, i, j);
            image->setColorAt(i, j, pixelColor);
        }
    }
    std::clog << "\rDone.                 \n";

    m_isImageRendered = true;
    image->printImagePPM(std::cout);
}

const Color& Renderer::calculateFinalColorAt(const HittableScene& world, int i, int j)
{
    Color finalColor(0, 0, 0);
	std::shared_ptr<Viewport> viewport = getCamera()->getViewport();
    const Point3d& cameraCenter = getCamera()->getCameraCenter();

    for (int k = 0; k < m_samplesPerPixel; ++k)
    {
        const Vec randomVector = sampleSquare();
        const Point3d& pixelCenter = viewport->getStartPixel() +
            (((double)i + randomVector.x()) * viewport->getUpDownDeltaVec()) +
            (((double)j + randomVector.y()) * viewport->getLeftRightDeltaVec());

        const Vec& rayDirection = pixelCenter - cameraCenter;
        const Ray ray(cameraCenter, rayDirection);

        finalColor += ray.calculateColor(world);
    }

    // Pixel color is divided, because of antialiasing.
	// We take average of colors gathered randomly from the sample.
	return m_scale * finalColor;
}