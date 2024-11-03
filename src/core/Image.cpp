#include "Image.h"

Image::Image(int32 height)
	: m_height(height)
{
	m_width = m_height * aspectRatio;
}

Image::Image(int32 height, int32 width)
	: m_height(height), m_width(width) 
{

}
