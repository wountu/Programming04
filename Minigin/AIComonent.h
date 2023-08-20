#pragma once
#include "BaseComponent.h"

#include <glm/vec2.hpp>

namespace dae
{
	class GameObject;
	class TransformComponent;
	class VisionComponent;
	class State;
	class BulletManager;
	class AIComponent final : public BaseComponent
	{
	public:
		AIComponent() = default;
		virtual ~AIComponent();
		AIComponent(const AIComponent& other) = delete;
		AIComponent& operator=(const AIComponent& other) = delete;
		AIComponent(AIComponent&& other) = delete;
		AIComponent& operator=(AIComponent&& other) = delete;

		virtual void Initialize(std::shared_ptr<GameObject> parent);
		virtual void Update() override;
		virtual void Render() const override;

		GameObject* GetParent() const;
		VisionComponent* GetVision() const;
	private:
		GameObject* m_Parent{ nullptr };
		VisionComponent* m_Vision{ nullptr };

		State* m_GhostState{ nullptr };
	};

}
