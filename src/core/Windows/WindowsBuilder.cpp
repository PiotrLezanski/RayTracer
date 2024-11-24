#include "WindowsBuilder.h"
#include "RenderedImageWindow.h"

#include <algorithm>

WindowsBuilder::WindowsBuilder()
{
	// List of windows
	m_windows.emplace_back(std::make_unique<RenderedImageWindow>());
}

void WindowsBuilder::buildUI()
{
	std::for_each(m_windows.begin(), m_windows.end(),
		[](const auto& window)
		{
			window->init();
		});
}
