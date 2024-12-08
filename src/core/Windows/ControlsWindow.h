#pragma once

#include "IWindow.h"

class ControlsWindow : public IWindow
{
public:
	ControlsWindow() = default;
	void init() override;
	void initImGuiFrame() override;
};
