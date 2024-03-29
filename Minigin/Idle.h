#pragma once
#include "State.h"
#include "AIComonent.h"

#include <glm/vec2.hpp>
#include <memory>

namespace dae
{
	class TransformComponent;
	class VisionComponent;
	class Idle final : public State
	{
	public:
		Idle() = default;
		virtual ~Idle() = default;

		Idle(const Idle& other) = delete;
		Idle& operator=(const Idle& other) = delete;
		Idle(Idle&& other) = delete;
		Idle& operator =(Idle&& other) = delete;

		void Initialize(float idleTime, AIComponent* ai);

		virtual void OnEnter() override;
		virtual State* Update() override;
		virtual void OnExit() override;
	private:
		float m_TimeIdle{ 0.f };
		float m_TimeBeingIdle{};

		AIComponent* m_AI{};
	};
}

