#pragma once
#include "BaseComponent.h"

namespace dae
{
	class GameObject;
	class TransformComponent;
	class VisionComponent;
	class PlayerState;
	class AIComponent final : public BaseComponent
	{
	public:
		AIComponent() = default;
		virtual ~AIComponent();
		AIComponent(const AIComponent& other) = delete;
		AIComponent& operator=(const AIComponent& other) = delete;
		AIComponent(AIComponent&& other) = delete;
		AIComponent& operator=(AIComponent&& other) = delete;

		virtual void Initialize(float tankSpeed, std::shared_ptr<GameObject> parent);
		virtual void Update() override;
		virtual void Render() const override;

		std::shared_ptr<TransformComponent> GetTransform() const;
		std::shared_ptr<VisionComponent> GetVision() const;
		float GetTankSpeed() const;
	private:
		GameObject* m_Parent{ nullptr };

		std::shared_ptr<TransformComponent> m_Transform{ nullptr };
		std::shared_ptr<VisionComponent> m_Vision{ nullptr };
		PlayerState* m_PlayerState{ nullptr };

		float m_TankSpeed{};

		int m_WaitFrames{ };
	};

}
