#include "RenderedImageWindow.h"

#include "imgui.h"

RenderedImageWindow::RenderedImageWindow()
{
}

void RenderedImageWindow::init()
{
    ImGui::Begin("Image Display");
    ImGui::Text("This is where the image will be displayed.");
    // Replace with your image rendering code
    //ImGui::Image((void*)(intptr_t)texture, ImVec2(imgWidth, imgHeight));
    ImGui::End();
}
