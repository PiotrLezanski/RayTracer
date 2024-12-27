#include "WindowsBuilder.h"
#include "RenderedImageWindow.h"
#include "ControlsWindow.h"

#include <algorithm>

WindowsBuilder::WindowsBuilder()
{
	// List of windows
	auto renderedImageWindow = std::make_shared<RenderedImageWindow>();
	// ControlsWindow needs RenderedImageWindow because it can influence it
	auto controlsWindow = std::make_shared<ControlsWindow>(renderedImageWindow);

	m_windows.emplace_back(renderedImageWindow);
	m_windows.emplace_back(controlsWindow);
}

void WindowsBuilder::buildUI()
{
	std::for_each(m_windows.begin(), m_windows.end(),
		[](const auto& window)
		{
			window->init();
		});
}
