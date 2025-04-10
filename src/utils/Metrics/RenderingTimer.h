#pragma once

#include <future>

using Time = std::chrono::time_point<std::chrono::steady_clock>;

class RenderingTimer
{
public:
	static RenderingTimer& getInstance()
	{
		static RenderingTimer instance;
		return instance;
	}

	void start()
	{
		m_endTime = Time();
		m_startTime = std::chrono::steady_clock::now();
	}

	void stop()
	{
		m_endTime = std::chrono::steady_clock::now();
	}

	float getValue()
	{
		return static_cast<std::chrono::duration<float>>(m_endTime - m_startTime).count();
	}

private:
	RenderingTimer() : m_startTime(), m_endTime() {}

	Time m_startTime;
	Time m_endTime;
};

inline RenderingTimer& RenderTimer = RenderingTimer::getInstance();
