#pragma once

#include "IWindow.h"
#include "RenderedImageWindow.h"
#include "../../utils/RenderedImageSettings.h"

class ControlsWindow : public IWindow
{
public:
	ControlsWindow(std::shared_ptr<RenderedImageWindow> renderedImageWindow);
	void init() override;
	void initImGuiFrame() override;

	auto getRenderedImageWindow() const { return m_renderedImageWindow; }
	auto& getImageSettings() const { return m_imageSettings; }

private:
	// It needs to have window with rendered image, 
	// as controls are affecting rendered and camera settings
	std::shared_ptr<RenderedImageWindow> m_renderedImageWindow;
	std::unique_ptr<RenderedImageSettings> m_imageSettings;
};
