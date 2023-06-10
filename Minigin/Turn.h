#pragma once
#include "PlayerState.h"
#include "AIComonent.h"

#include <glm/vec2.hpp>
#include <memory>

namespace dae
{
	class TransformComponent;
	class Turn final : public PlayerState
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
		virtual PlayerState* HandleInput() override;
		virtual void OnExit() override;
	private:
		std::shared_ptr<TransformComponent> m_Transform{};
		AIComponent* m_AI{};
	};
}

