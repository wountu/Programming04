#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

#include <glm/vec2.hpp>
#include <vector>

namespace dae
{
	class TransformComponent;
	class GameObject;

	struct Vision
	{
		glm::vec2 startVision{};
		glm::vec2 endVision{};
		glm::vec2 direction{};
	};

	class VisionComponent final : public BaseComponent
	{
	public:
		VisionComponent() = default;
		virtual ~VisionComponent() = default;
		VisionComponent(const VisionComponent& other) = delete;
		VisionComponent& operator=(const VisionComponent& other) = delete;
		VisionComponent(VisionComponent&& other) = delete;
		VisionComponent& operator=(VisionComponent&& other) = delete;

		virtual void Initialize(std::shared_ptr<GameObject> parent, float visionLength);
		virtual void Update() override;
		virtual void Render() const override;

		std::vector<GameObject*> SeenObjects() const;
		std::vector<GameObject*> ClosestSeenObjects() const;

		glm::vec2 GetStartVision() const;
		glm::vec2 GetEndVision() const;
		glm::vec2 GetDirection() const;
	private:
		GameObject* m_Parent{ nullptr };

		std::vector<Vision> m_Visions{};

		glm::vec2 m_StartVision{};
		glm::vec2 m_EndVision{};
		glm::vec2 m_Direction{};

		float m_VisionLength{};

		glm::vec2 m_Offset{};

		std::shared_ptr<TransformComponent> m_Transform{};
	};

}

