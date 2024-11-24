#pragma once

#include "MainUI.h"

class App
{
public:
	void init();

private:
	std::unique_ptr<MainUI> m_mainUI;
};

void App::init()
{
	m_mainUI = std::make_unique<MainUI>();
	m_mainUI->init();
}