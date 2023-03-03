#pragma once
#include "BaseComponent.h"
#include <glm/vec2.hpp>

namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent() = default;
		virtual ~TransformComponent();
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;

		virtual void Initialize(const glm::vec2& pos, std::shared_ptr<GameObject> parent);

		void ChangePosition(glm::vec2 pos);
		glm::vec2 GetPosition() const;
	private:
		glm::vec2 m_position;
	};

}

