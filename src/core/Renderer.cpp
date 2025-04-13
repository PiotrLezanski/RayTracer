#include "Renderer.h"

#include "../utils/Metrics/RayIntersectionCounter.h"
#include "../utils/Metrics/RenderingTimer.h"

namespace
{
    Vec sampleSquare()
	{
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square
        return Vec(randomDouble() - 0.5, randomDouble() - 0.5, 0);
    }
}

Renderer::Renderer(std::shared_ptr<Camera> camera, std::unique_ptr<HittableScene> world)
	: m_camera(camera), m_world(std::move(world)), m_textureId(0)
{}

void Renderer::startRendering()
{
    if (isImageRendered())
        return;

    if (!m_world)
        return;

    std::shared_ptr<Image> image = getImage();
    if (!image)
        return;

    // Image
    int32 imageHeight = image->height();

    // Render
    initializeTexture();

    std::vector<std::thread> renderingThreads;
    renderingThreads.reserve(imageHeight);

    std::clog << "Rendering started!" << std::endl;

    // start timer
    RenderTimer.start();

    for (int32 i = 0; i < imageHeight; ++i)
    {
        renderingThreads.emplace_back(&Renderer::renderRow, this, i);
    }

    // Join all threads after creation
    for (std::thread& thread : renderingThreads)
    {
        if (thread.joinable())
            thread.join();
    }

    // Image object now contains rendered image,
    // so we need to update glad texture, which is shown in the UI
    for (int i = 0; i < imageHeight; ++i)
        updateTextureRow(i);

    // stop timer
    RenderTimer.stop();

    std::clog << "\nRendering finished!" << std::endl;
    m_isImageRendered = true;
}

void Renderer::stopRendering()
{
    m_textureId = 0;
    m_isImageRendered = false;
    IntersectionCounter.reset();
}

void Renderer::rerender()
{
    stopRendering();
    startRendering();
}

RegenerationType Renderer::overrideSetting(const RenderedImageSettings& settings)
{
    unsigned int regenType = RegenerationType::RegenerateNone;

    if (getCamera()->getLookFrom() != settings.cameraLookFrom)
    {
        regenType |= RegenerationType::RegenerateAll;
        getCamera()->setLookFrom(settings.cameraLookFrom);
    }
    
    if (getCamera()->getLookAt() != settings.cameraLookAt)
    {
        regenType |= RegenerationType::RegenerateAll;
        getCamera()->setLookAt(settings.cameraLookAt);
    }
    
    if (getCamera()->getFieldOfView() != settings.fieldOfView)
    {
        regenType |= RegenerationType::RegenerateAll;
        getCamera()->setFieldOfView(settings.fieldOfView);
    }
    
    if (getSamplesPerPixel() != settings.samplesPerPixel)
    {
        regenType |= RegenerationType::RegenerateRenderer;
        setSamplesPerPixel(settings.samplesPerPixel);
    }

    if (getMaxRayRecursionDepth() != settings.maxRecursionDepth)
    {
        regenType |= RegenerationType::RegenerateRenderer;
        setMaxRayRecursionDepth(settings.maxRecursionDepth);
    }

    return static_cast<RegenerationType>(regenType);
}

RenderedImageSettings Renderer::getImageSettings() const
{
    RenderedImageSettings settings;
    settings.cameraLookFrom = getCamera()->getLookFrom();
    settings.cameraLookAt = getCamera()->getLookAt();
    settings.fieldOfView = getCamera()->getFieldOfView();
    settings.samplesPerPixel = getSamplesPerPixel();
    settings.maxRecursionDepth = getMaxRayRecursionDepth();
    return settings;
}

void Renderer::initializeTexture()
{
    const int32 imageWidth = getImage()->width();
    const int32 imageHeight = getImage()->height();

    // Generate and bind the texture
    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);

    // Allocate empty texture memory
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    //glGenerateMipmap(GL_TEXTURE_2D);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Renderer::setSamplesPerPixel(int samplesPerPixel)
{
    m_samplesPerPixel = samplesPerPixel;
    m_scale = 1.0 / m_samplesPerPixel;
}

void Renderer::renderRow(int32 rowIndex)
{
    if (m_stopRendering)
        return;

    for (int32 j = 0; j < getImage()->width(); j++)
    {
        const Color& pixelColor = calculateFinalColorAt(rowIndex, j);
        getImage()->setColorAt(rowIndex, j, pixelColor);
    }
}

void Renderer::updateTextureRow(int32 rowIndex)
{
    const int32 imageWidth = getImage()->width();
    std::vector<uint8_t> rowTextureData(imageWidth * 4);

    for (int32 x = 0; x < imageWidth; ++x) {
        const Color& c = getImage()->getColorAt(rowIndex, x);

        rowTextureData[x * 4 + 0] = uint8_t(std::fabs(c[0] * 255));
        rowTextureData[x * 4 + 1] = uint8_t(std::fabs(c[1] * 255));
        rowTextureData[x * 4 + 2] = uint8_t(std::fabs(c[2] * 255));
        rowTextureData[x * 4 + 3] = 255;
    }

    // Bind the texture to update it
    glBindTexture(GL_TEXTURE_2D, m_textureId);

    // Upload texture row data
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, rowIndex, imageWidth, 1,
        GL_RGBA, GL_UNSIGNED_BYTE, rowTextureData.data());
}

const Color& Renderer::calculateFinalColorAt(int i, int j, bool gammaCorrect)
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

        // We create imageWidth * imageHeight * m_samplesPerPixel Rays that are hit into the scene.
        // Every ray individually hits the Scene in Ray::calculateColor.
        // In my BVH structure that means that every ray hits BVH_Tree root.
        const Vec& rayDirection = pixelCenter - cameraCenter;
        const Ray ray(cameraCenter, rayDirection);

        finalColor += ray.calculateColor(*m_world, m_maxRayRecursionDepth);
    }

    // Pixel color is divided, because of antialiasing.
	// We take average of colors gathered randomly from the sample.
    finalColor = m_scale * finalColor;

    if (gammaCorrect)
        linearToGamma(finalColor);

	return finalColor;
}