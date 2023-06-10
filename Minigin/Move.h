#pragma once
#include "PlayerState.h"

#include <glm/vec2.hpp>
#include <memory>

namespace dae
{
	class TransformComponent;
	class VisionComponent;
	class Move final : public PlayerState
	{
	public:
		Move(std::shared_ptr<TransformComponent> transform, std::shared_ptr<VisionComponent> vision, float speed);
		virtual ~Move() = default;

		Move(const Move& other) = delete;
		Move& operator=(const Move& other) = delete;
		Move(Move&& other) = delete;
		Move& operator =(Move&& other) = delete;

		virtual void OnEnter() override;
		virtual PlayerState* HandleInput() override;
		virtual void OnExit() override;
	private:
		std::shared_ptr<TransformComponent> m_Transform;
		std::shared_ptr<VisionComponent> m_Vision;

		glm::vec2 m_Dir{};
		float m_Speed;
	};
}

