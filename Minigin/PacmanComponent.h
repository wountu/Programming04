#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"
#include "TransformComponent.h"

namespace dae
{
	class PacmanComponent final : public BaseComponent
	{
	public:
		PacmanComponent() = default;
		virtual ~PacmanComponent();
		PacmanComponent(const PacmanComponent& other) = delete;
		PacmanComponent& operator=(const PacmanComponent& other) = delete;
		PacmanComponent(PacmanComponent&& other) = delete;
		PacmanComponent& operator=(PacmanComponent&& other) = delete;

		virtual void Initialize(std::shared_ptr<GameObject> parent, const float movementSpeed);
		virtual void Update() override;

		void SetDirection(glm::vec2 dir);
	private:
		glm::vec2 m_Direction{};
		std::shared_ptr<TransformComponent> m_Transform{};

		float m_MovementSpeed{};
	};
}
