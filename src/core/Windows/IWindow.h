#pragma once

class IWindow
{
public:
	virtual ~IWindow() = default;
	virtual void init() = 0;
};