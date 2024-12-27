#include "ControlsWindow.h"

ControlsWindow::ControlsWindow(std::shared_ptr<RenderedImageWindow> renderedImageWindow)
    : m_renderedImageWindow(renderedImageWindow)
{
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
        std::shared_ptr<Renderer> renderer = m_renderedImageWindow->getRenderer();

        ImGui::Begin("Camera Settings", &showCameraWindow);

        // Camera position
        ImGui::Text("Camera Position:");
        std::array<float, 3> cameraPosition = m_renderedImageWindow->getCamera()->getLookFrom().asFloatArray();
        ImGui::InputFloat3("(x, y, z)", cameraPosition.data());

        // Camera target
        ImGui::Text("Camera Target:");
        std::array<float, 3> cameraTarget = m_renderedImageWindow->getCamera()->getLookAt().asFloatArray();
        ImGui::InputFloat3("(x, y, z)", cameraTarget.data());

        // Field of view slider
        ImGui::Text("Field of View (degrees):");
        float fieldOfView = m_renderedImageWindow->getCamera()->getFieldOfView();
        ImGui::SliderFloat("FOV", &fieldOfView, 1.0f, 120.0f);

        // Samples per pixel
        ImGui::Text("Samples Per Pixel:");
        int samplesPerPixel = renderer->getSamplesPerPixel();
        ImGui::InputInt("Samples", &samplesPerPixel);

        // Max recursion depth
        ImGui::Text("Max Ray Recursion Depth:");
        int maxRayRecursionDepth = renderer->getMaxRayRecursionDepth();
        ImGui::InputInt("Recursion Depth", &maxRayRecursionDepth);

        if (ImGui::Button("Refresh Image"))
        {
            // Set new values
            renderer->getCamera()->setLookFrom(Point3d(cameraPosition[0], cameraPosition[1], cameraPosition[2]));
            renderer->getCamera()->setLookAt(Point3d(cameraTarget[0], cameraTarget[1], cameraTarget[2]));
            renderer->getCamera()->setFieldOfView(fieldOfView);
            renderer->setSamplesPerPixel(samplesPerPixel);
            renderer->setMaxRayRecursionDepth(maxRayRecursionDepth);

            // Then rerender
            //m_renderedImageWindow->getRenderer()->
        }

        if (ImGui::Button("Close"))
            showCameraWindow = false;

        ImGui::End();
    }
}