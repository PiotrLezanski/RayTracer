#pragma once

#include "glad/glad.h"
#include "imgui.h"
#include "imgui_impl_opengl3_loader.h"
#include <GLFW/glfw3.h>

class IWindow
{
public:
	// General initialization of Window contents
	virtual void init() = 0;

	virtual ~IWindow() = default;

protected:
	// Initialization of ImGui specific GUI
	// Called by main init() method
	// This method will usually use some member variables
	// so initialize them before calling this
	virtual void initImGuiFrame() = 0;
};