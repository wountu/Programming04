#include <iostream>
#include "TimeClass.h"

namespace dae
{
	void TimeClass::Initialize()
	{
		m_timeLastFrame = std::chrono::high_resolution_clock::now();

	}

	void TimeClass::Update()
	{
		m_timeThisFrame = std::chrono::high_resolution_clock::now();
		m_elapsed = std::chrono::duration<float>(m_timeThisFrame - m_timeLastFrame).count();
		m_lag += m_elapsed;

		m_fps = int(1.f / m_elapsed);
		//std::cout << m_fps << "\n";

		m_timeLastFrame = m_timeThisFrame;
	}

	int TimeClass::GetFps() const
	{
		//std::cout << m_fps << "\n";
		return m_fps;
	}

	void TimeClass::SetLag(float lag)
	{
		m_lag = lag;
	}

	float TimeClass::GetLag() const
	{
		return m_lag;
	}

	float TimeClass::GetElapsed() const
	{
		return m_elapsed;
	}

	std::chrono::steady_clock::time_point TimeClass::GetTotalTime() const
	{ 
		return m_timeThisFrame;
	}

}

