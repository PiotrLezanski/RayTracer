#include "StatsWindow.h"
#include "../../utils/Metrics/RayIntersectionCounter.h"
#include "../../utils/Metrics/RenderingTimer.h"
#include "../../utils/utils.h"

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
	ImGui::Text("Ray-object intersection checks: %s",
		formatLargeIntegers(IntersectionCounter.getValue()).c_str());

	ImGui::End();
}
