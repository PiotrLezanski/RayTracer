#pragma once

#include "IWindow.h"

class StatsWindow : public IWindow
{
public:
	void init() override;

protected:
	void initImGuiFrame() override;
};
