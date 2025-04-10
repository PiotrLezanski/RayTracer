#include "ControlsWindow.h"
#include "RenderedImageWindow.h"
#include "StatsWindow.h"
#include "WindowsBuilder.h"

#include <algorithm>

WindowsBuilder::WindowsBuilder()
{
	// List of windows
	auto renderedImageWindow = std::make_shared<RenderedImageWindow>();

	// ControlsWindow needs RenderedImageWindow because it can influence it
	auto controlsWindow = std::make_shared<ControlsWindow>(renderedImageWindow);

	auto statsWindow = std::make_shared<StatsWindow>();

	m_windows.emplace_back(renderedImageWindow);
	m_windows.emplace_back(controlsWindow);
	m_windows.emplace_back(statsWindow);
}

void WindowsBuilder::buildUI()
{
	std::for_each(m_windows.begin(), m_windows.end(),
		[](const auto& window)
		{
			window->init();
		});
}
