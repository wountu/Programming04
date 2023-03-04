#pragma once
#include <chrono>

#include "Singleton.h"

namespace dae
{
	class TimeClass final : public Singleton<TimeClass>
	{
	public:
		TimeClass() = default;
		virtual ~TimeClass() = default;
		TimeClass(const TimeClass& other) = delete;
		TimeClass& operator=(const TimeClass& other) = delete;
		TimeClass(TimeClass&& other) = delete;
		TimeClass& operator=(TimeClass&& other) = delete;

		void Initialize();
		void Update();

		int GetFps() const;

		void SetLag(float lag);
		float GetLag() const;
		float GetElapsed() const;

		std::chrono::steady_clock::time_point GetTotalTime() const;
	private:
		std::chrono::steady_clock::time_point m_timeLastFrame;
		std::chrono::steady_clock::time_point m_timeThisFrame;
		std::chrono::high_resolution_clock m_currentTime;

		int m_fps{};
		float m_lag{};
		float m_elapsed{};
	};
}


