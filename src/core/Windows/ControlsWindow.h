#pragma once

#include "IWindow.h"
#include "RenderedImageWindow.h"

class ControlsWindow : public IWindow
{
public:
	ControlsWindow(std::shared_ptr<RenderedImageWindow> renderedImageWindow);
	void init() override;
	void initImGuiFrame() override;

private:
	// It needs to have window with rendered image, 
	// as controls are affecting rendered and camera settings
	std::shared_ptr<RenderedImageWindow> m_renderedImageWindow;
};
