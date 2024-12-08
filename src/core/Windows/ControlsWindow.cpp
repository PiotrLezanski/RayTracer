#include "ControlsWindow.h"

void ControlsWindow::init()
{
    initImGuiFrame();
}

void ControlsWindow::initImGuiFrame()
{
    bool showAnotherWindow = true;
    if (showAnotherWindow) 
    {
        ImGui::Begin("Controls", &showAnotherWindow);
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me")) {
            showAnotherWindow = false;
        }
        ImGui::End();
    }
}