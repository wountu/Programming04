#pragma once
#include <glm/vec2.hpp>
#include <memory>

#include "BaseComponent.h"
#include "TransformComponent.h"


namespace dae
{
	class RotateComponent final : public BaseComponent
	{
	public:
		RotateComponent() = default;
		virtual ~RotateComponent() = default;
		RotateComponent(const RotateComponent& other)			 = delete;
		RotateComponent& operator=(const RotateComponent& other) = delete;
		RotateComponent(RotateComponent&& other)				 = delete;
		RotateComponent& operator=(RotateComponent&& other)		 = delete;

		virtual void Initialize(std::shared_ptr<GameObject> parent, float radius = 0.f);
		virtual void Update() override;
	private:
		float m_angle{};
		float m_radius{};

		glm::vec2 m_position{};

		std::shared_ptr<TransformComponent> m_transform{ nullptr };
	};
}


