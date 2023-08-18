#pragma once
#include "State.h"
#include "AIComonent.h"

#include <glm/vec2.hpp>
#include <memory>

namespace dae
{
	class TransformComponent;
	class Turn final : public State
	{
	public:
		Turn() = default;
		virtual ~Turn() = default;

		Turn(const Turn& other) = delete;
		Turn& operator=(const Turn& other) = delete;
		Turn(Turn&& other) = delete;
		Turn& operator =(Turn&& other) = delete;

		void Initialize(AIComponent* ai, std::shared_ptr<TransformComponent> transform);

		virtual void OnEnter() override;
		virtual State* Update() override;
		virtual void OnExit() override;
	private:
		std::shared_ptr<TransformComponent> m_Transform{};
		AIComponent* m_AI{};
	};
}

