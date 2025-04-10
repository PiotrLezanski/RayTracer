#include "StatsWindow.h"
#include "../../utils/RayIntersectionCounter.h"

void StatsWindow::init()
{
	initImGuiFrame();
}

void StatsWindow::initImGuiFrame()
{
	ImGui::Begin("Rendering statistics");
	ImGui::Text("Number of ray-object intersection checks from previous render: %d",
		IntersectionCounter.getValue());

	ImGui::End();
}
