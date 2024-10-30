#include "Renderer.h"

using Color = Vec3<double>;

Renderer::Renderer(std::shared_ptr<Image> image)
	: m_image(image)
{

}

void Renderer::render()
{
    // Image
    int32 image_width = m_image->width();
    int32 image_height = m_image->height();

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = 0; j < image_height; j++)
    {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++)
        {
            const Color& pixelColor = Color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.0);
            ColorUtils::printColor(std::cout, pixelColor);
        }
    }
    std::clog << "\rDone.                 \n";
}