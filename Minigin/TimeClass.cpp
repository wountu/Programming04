#include <iostream>
#include "TimeClass.h"

namespace dae
{
	void TimeClass::Initialize()
	{
		m_fps = 0;
		m_lag = 0;
		m_timeLastFrame = std::chrono::high_resolution_clock::now();
	}

	void TimeClass::Update()
	{
		m_timeThisFrame = std::chrono::high_resolution_clock::now();
		float elapsedSec = std::chrono::duration<float>(m_timeThisFrame - m_timeLastFrame).count();
		m_lag += elapsedSec;

		m_fps = int(1.f / elapsedSec);
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

	std::chrono::steady_clock::time_point TimeClass::GetTotalTime() const
	{ 
		return m_timeThisFrame;
	}

}

