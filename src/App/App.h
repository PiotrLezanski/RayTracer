#pragma once

#include "MainUI.h"

class App
{
public:
	void init();

private:
	void prepareMainUI();

private:
	std::unique_ptr<MainUI> m_mainUI;
};