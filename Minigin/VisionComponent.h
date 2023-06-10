#pragma once
#include "BaseComponent.h"
#include <glm/vec2.hpp>

namespace dae
{
	class TransformComponent;
	class GameObject;
	class VisionComponent final : public BaseComponent
	{
	public:
		VisionComponent() = default;
		virtual ~VisionComponent() = default;
		VisionComponent(const VisionComponent& other) = delete;
		VisionComponent& operator=(const VisionComponent& other) = delete;
		VisionComponent(VisionComponent&& other) = delete;
		VisionComponent& operator=(VisionComponent&& other) = delete;

		virtual void Initialize(std::shared_ptr<GameObject> parent, float visionLength, glm::vec2 offset = glm::vec2{});
		virtual void Update() override;
		virtual void Render() const override;

		glm::vec2 GetStartVision() const;
		glm::vec2 GetEndVision() const;
		glm::vec2 GetDirection() const;
	private:
		GameObject* m_Parent{ nullptr };

		glm::vec2 m_StartVision{};
		glm::vec2 m_EndVision{};
		glm::vec2 m_Direction{};

		float m_VisionLength{};

		glm::vec2 m_Offset{};

		std::shared_ptr<TransformComponent> m_Transform{};
	};

}

