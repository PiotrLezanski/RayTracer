#pragma once

#include <atomic>

// Singleton class to count number of ray-object intersection checks.
// It's good metric to compare brute force and BVH solutions.
class RayIntersectionCounter
{
public:
	static RayIntersectionCounter& getInstance()
	{
		static RayIntersectionCounter instance;
		return instance;
	}

	void increment()
	{
		m_counter.fetch_add(1, std::memory_order_relaxed);
	}

	void reset()
	{
		m_counter.store(0, std::memory_order_relaxed);
	}

	size_t getValue() const
	{
		return m_counter.load(std::memory_order_relaxed);
	}

private:
	RayIntersectionCounter() : m_counter(0) {}

	std::atomic<size_t> m_counter = 0;
};

inline RayIntersectionCounter& IntersectionCounter = RayIntersectionCounter::getInstance();