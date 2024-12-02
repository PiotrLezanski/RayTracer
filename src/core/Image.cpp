#include "Image.h"

#include <algorithm>

Image::Image(int32 height)
	: m_height(height)
{
	m_width = m_height * m_aspectRatio;
	m_data = std::vector<std::vector<Color>>(m_height, 
				std::vector<Color>(m_width, DEFAULT_COLOR));
}

void Image::printColorToRGB(std::ostream& out, const Color& color) const
{
	const auto r = linearToGamma(color.x());
	const auto g = linearToGamma(color.y());
	const auto b = linearToGamma(color.z());

	out << static_cast<int>(256 * std::clamp(r, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * std::clamp(g, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * std::clamp(b, 0.0, 0.999)) << ' ';
}

Color& Image::getColorAt(int32 x, int32 y)
{
	x = std::clamp(x, (int32)0, height()-1);
	y = std::clamp(y, (int32)0, width()-1);
	return m_data[x][y];
}

void Image::setColorAt(uint32_t x, uint32_t y, const Color& newColor)
{
	if (x >= height() || y >= width())
		return;

	m_data[x][y] = newColor;
}

void Image::printImagePPM(std::ostream& out) const
{
	out << "P3\n" << width() << ' ' << height() << "\n255\n";
	for (const auto& row : m_data) 
	{
		for (const auto& pixelColor : row) 
		{
			printColorToRGB(out, pixelColor);
		}
		out << "\n";
	}
}