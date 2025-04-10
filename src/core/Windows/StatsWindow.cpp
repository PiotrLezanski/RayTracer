#include "StatsWindow.h"
#include "../../utils/Metrics/RayIntersectionCounter.h"
#include "../../utils/Metrics/RenderingTimer.h"

void StatsWindow::init()
{
	initImGuiFrame();
}

void StatsWindow::initImGuiFrame()
{
	ImGui::Begin("Rendering statistics");

	// Rendering time
	ImGui::Text("Rendering time: %.2f s",
		RenderTimer.getValue());

	// Number of intersection checks
	ImGui::Text("Ray-object intersection checks: %d",
		IntersectionCounter.getValue());

	ImGui::End();
}
