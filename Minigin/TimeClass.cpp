#include <iostream>
#include "TimeClass.h"

namespace dae
{
	void TimeClass::Initialize()
	{
		m_fps = 0;
		m_timeLastFrame = std::chrono::high_resolution_clock::now();
	}

	void TimeClass::Update()
	{
		m_timeThisFrame = std::chrono::high_resolution_clock::now();
		float elapsedSec = std::chrono::duration<float>(m_timeThisFrame - m_timeLastFrame).count();
		//m_counter += elapsedSec;

		m_fps = int(1.f / elapsedSec);
		//std::cout << m_fps << "\n";

		m_timeLastFrame = m_timeThisFrame;
	}

	int TimeClass::GetFps() const
	{
		//std::cout << m_fps << "\n";
		return m_fps;
	}

}

