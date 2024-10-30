#pragma once

#include "../utils/utils.h"

class Image
{
public:
	Image();
	Image(int32 height, int32 width);

	[[nodiscard]] int32 height() { return m_height; }
	[[nodiscard]] int32 width() { return m_width; }
private:
	int32 m_height;
	int32 m_width;
};