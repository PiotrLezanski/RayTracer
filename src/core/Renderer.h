#pragma once
#include <iostream>

#include "../utils/utils.h"
#include "Image.h"
#include "../utils/Color.h"

class Renderer
{
public:
	explicit Renderer(std::shared_ptr<Image> image);
	void render();

private:
	std::shared_ptr<Image> m_image;
};