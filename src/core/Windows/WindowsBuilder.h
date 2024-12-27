#pragma once

#include "IWindow.h"

#include <vector>
#include <memory>

// Class to build ImGui windows
class WindowsBuilder
{
public:
	WindowsBuilder();
	void buildUI();

private:
	std::vector<std::shared_ptr<IWindow>> m_windows;
};