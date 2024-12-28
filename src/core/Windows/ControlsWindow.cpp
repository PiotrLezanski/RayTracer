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
        std::shared_ptr<Camera> camera = renderer->getCamera();

        ImGui::Begin("Camera Settings", &showCameraWindow);

        // Camera position
        ImGui::Text("Camera Position:");
        Point3d& cameraLookFrom = getImageSettings()->cameraLookFrom;

        // Separate entries for each coordinate,
        // as ImGui does not support it natively
        ImGui::InputDouble("X", &cameraLookFrom.x());
        ImGui::InputDouble("Y", &cameraLookFrom.y());
        ImGui::InputDouble("Z", &cameraLookFrom.z());

        // Camera target
        ImGui::Text("Camera Target:");
        Point3d& cameraLookAt = getImageSettings()->cameraLookAt;
        ImGui::InputDouble("X", &cameraLookAt.x());
        ImGui::InputDouble("Y", &cameraLookAt.y());
        ImGui::InputDouble("Z", &cameraLookAt.z());

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
            bool rerender = false;

            // If "Refresh Image" is pressed, update camera and renderer settings
            // only if at least one of the parameters changed
            if (camera->getLookFrom() != cameraLookFrom)
            {
                camera->setLookFrom(cameraLookFrom);
                rerender = true;
            }
            if (camera->getLookAt() != cameraLookAt)
            {
                camera->setLookFrom(cameraLookAt);
                rerender = true;
            }
            if (camera->getFieldOfView() != fieldOfView)
            {
                camera->setFieldOfView(fieldOfView);
                rerender = true;
            }
            if (renderer->getSamplesPerPixel() != samplesPerPixel)
            {
                renderer->setSamplesPerPixel(samplesPerPixel);
                rerender = true;
            }
            if (renderer->getMaxRayRecursionDepth() != maxRayRecursionDepth)
            {
                renderer->setMaxRayRecursionDepth(maxRayRecursionDepth);
                rerender = true;
            }

            if (rerender)
                getRenderedImageWindow()->getRenderer()->rerender();
        }

        if (ImGui::Button("Close"))
            showCameraWindow = false;

        ImGui::End();
    }
}