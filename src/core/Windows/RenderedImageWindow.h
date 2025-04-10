#pragma once

#include "IWindow.h"
#include "../Image.h"
#include "../Camera.h"
#include "../Renderer.h"

#include <memory>

class RenderedImageWindow : public IWindow
{
public:
	RenderedImageWindow();
	void init() override;

	std::shared_ptr<Image> getImage() { return m_image; }
	std::shared_ptr<Camera> getCamera() { return m_camera; }
	std::shared_ptr<Renderer> getRenderer() { return m_renderer; }

protected:
	void initImGuiFrame() override;

private:
	std::shared_ptr<Image> m_image;
	std::shared_ptr<Camera> m_camera;
	std::shared_ptr<Renderer> m_renderer;
};