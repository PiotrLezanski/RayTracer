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
    if (!image)
        return;

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
}

GLuint Renderer::createTextureFromImage() const
{
    if (!isImageRendered())
        return GLuint();

    const int32 imageWidth = getImage()->width();
    const int32 imageHeight = getImage()->height();

    // Resize and fill renderTexture with pixel data
    std::vector<uint8_t> renderTexture;
    renderTexture.resize(4 * imageWidth * imageHeight);

    for (int32 x = 0; x < imageHeight; ++x) {
        for (int32 y = 0; y < imageWidth; ++y) {
            const Color& c = getImage()->getColorAt(x, y);
            renderTexture[(x * imageWidth + y) * 4 + 0] = uint8_t(std::fabs(c[0] * 255));
            renderTexture[(x * imageWidth + y) * 4 + 1] = uint8_t(std::fabs(c[1] * 255));
            renderTexture[(x * imageWidth + y) * 4 + 2] = uint8_t(std::fabs(c[2] * 255));
            renderTexture[(x * imageWidth + y) * 4 + 3] = 255;
        }
    }

    // Generate and bind texture
    unsigned textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Upload texture data with correct type
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight,
        0, GL_RGBA, GL_UNSIGNED_BYTE, renderTexture.data());

	// Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}

const Color& Renderer::calculateFinalColorAt(const HittableScene& world, int i, int j, bool gammaCorrect)
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

        finalColor += ray.calculateColor(world, m_maxRayRecursionDepth);
    }

    // Pixel color is divided, because of antialiasing.
	// We take average of colors gathered randomly from the sample.
    finalColor = m_scale * finalColor;

    if (gammaCorrect)
        linearToGamma(finalColor);

	return finalColor;
}