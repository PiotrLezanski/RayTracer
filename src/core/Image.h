#pragma once

#include "../utils/utils.h"

class Image
{
public:
	Image() = default;
	// when just height is given, width will be equal to height * aspectRatio
	Image(int32 height);
	Image(int32 height, int32 width);

	[[nodiscard]] int32 height() const { return m_height; }
	[[nodiscard]] int32 width() const { return m_width; }
private:
	int32 m_height;
	int32 m_width;
	double aspectRatio = 16.0 / 9.0;
};