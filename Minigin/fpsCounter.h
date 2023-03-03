#pragma once
#include <memory>
#include <chrono>

#include "BaseComponent.h"
#include "TextObject.h"

namespace dae
{
	class fpsCounter final : public BaseComponent
	{
	public:
		fpsCounter() = default;
		virtual ~fpsCounter() = default;
		fpsCounter(const fpsCounter& other)			   = delete;
		fpsCounter& operator=(const fpsCounter& other) = delete;
		fpsCounter(fpsCounter&& other)				   = delete;
		fpsCounter& operator=(fpsCounter&& other)	   = delete;

		virtual void Initialize(std::shared_ptr<GameObject> parent) override;
		virtual void Update() override;

		int GetFps() const;
	private:
		std::chrono::steady_clock::time_point m_timeLastFrame;
		std::chrono::steady_clock::time_point m_timeThisFrame;

		float m_timeCounter{};
		int m_Counter{};
		int m_fps{};

		std::shared_ptr<TextObject> m_text{};
	};
}

