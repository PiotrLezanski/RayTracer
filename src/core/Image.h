#pragma once

#include "../utils/utils.h"

class Image
{
public:
	Image() = default;
	// when just height is given, width will be equal to height * aspectRatio
	Image(int32 height);

	[[nodiscard]] int32 height() const { return m_height; }
	[[nodiscard]] int32 width() const { return m_width; }

	[[nodiscard]] void printColorToRGB(std::ostream& out, const Color& color) const;
	[[nodiscard]] Color& getColorAt(uint8_t x, uint8_t y);
	void setColorAt(uint8_t x, uint8_t y, const Color& newColor);
	void printImagePPM(std::ostream& out) const;

private:
	int32 m_height;
	int32 m_width;
	double m_aspectRatio = 16.0 / 9.0;

	// 2d vector of color corespoding to every pixel
	// Color is stored in normalized RGB
	// Size is width * height
	std::vector<std::vector<Color>> m_data;
};