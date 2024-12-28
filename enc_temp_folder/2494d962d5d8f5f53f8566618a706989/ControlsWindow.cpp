#include "ControlsWindow.h"

ControlsWindow::ControlsWindow(std::shared_ptr<RenderedImageWindow> renderedImageWindow)
    : m_renderedImageWindow(renderedImageWindow)
{
    m_imageSettings = std::make_unique<RenderedImageSettings>();
}

void ControlsWindow::init()
{
    initImGuiFrame();
}

void ControlsWindow::initImGuiFrame()
{
    bool showCameraWindow = true;
    if (showCameraWindow)
    {
        std::shared_ptr<Renderer> renderer = getRenderedImageWindow()->getRenderer();

        ImGui::Begin("Camera Settings", &showCameraWindow);

        // Camera position
        ImGui::Text("Camera Position:");
        Point3d& cameraLookFrom = getImageSettings()->cameraLookFrom;
        ImGui::InputFloat3("(x, y, z)", cameraLookFrom.asFloatArray().data());

        // Camera target
        ImGui::Text("Camera Target:");
        Point3d& cameraLookAt = getImageSettings()->cameraLookAt;
        ImGui::InputFloat3("(x, y, z)", cameraLookAt.asFloatArray().data());

        // Field of view slider
        ImGui::Text("Field of View (degrees):");
        float& fieldOfView = getImageSettings()->fieldOfView;
        ImGui::SliderFloat("FOV", &fieldOfView, 1.0f, 120.0f);

        // Samples per pixel
        ImGui::Text("Samples Per Pixel:");
        int& samplesPerPixel = getImageSettings()->samplesPerPixel;
        ImGui::InputInt("Samples", &samplesPerPixel);

        // Max recursion depth
        ImGui::Text("Max Ray Recursion Depth:");
        int& maxRayRecursionDepth = getImageSettings()->maxRecursionDepth;
        ImGui::InputInt("Recursion Depth", &maxRayRecursionDepth);

        if (ImGui::Button("Refresh Image"))
        {
            // If "Refresh Image" is pressed, update camera and renderer settings
            renderer->getCamera()->setLookFrom(cameraLookFrom);
            renderer->getCamera()->setLookAt(cameraLookAt);
            renderer->getCamera()->setFieldOfView(fieldOfView);
            renderer->setSamplesPerPixel(samplesPerPixel);
            renderer->setMaxRayRecursionDepth(maxRayRecursionDepth);

            // Then rerender
            getRenderedImageWindow()->getRenderer()->rerender();
        }

        if (ImGui::Button("Close"))
            showCameraWindow = false;

        ImGui::End();
    }
}