#pragma once
#include "BaseComponent.h"

#include <glm/vec2.hpp>

namespace dae
{
	class GameObject;
	class TransformComponent;
	class VisionComponent;
	class PlayerState;
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

		virtual void Initialize(float tankSpeed, std::shared_ptr<GameObject> parent, std::shared_ptr<BulletManager> bulletManager);
		virtual void Update() override;
		virtual void Render() const override;

		std::shared_ptr<TransformComponent> GetTransform() const;
		std::shared_ptr<VisionComponent> GetVision() const;
		std::shared_ptr<BulletManager> GetBulletManager() const;
		
		float GetTankSpeed() const;

		void SetTargetDir(glm::vec2 targetDir);
		glm::vec2 GetTargetDir() const;

		void Shot();
		bool GetCanShoot() const;

		void Reset();
	private:
		GameObject* m_Parent{ nullptr };

		std::shared_ptr<TransformComponent> m_Transform{ nullptr };
		std::shared_ptr<VisionComponent> m_Vision{ nullptr };
		std::shared_ptr<BulletManager> m_BulletManager{ nullptr };
		PlayerState* m_PlayerState{ nullptr };


		glm::vec2 m_TargerDir{};

		float m_TankSpeed{};

		int m_WaitFrames{ };

		const float m_TimeInBetweenBullets{ 1.5f };
		float m_TimeSinceLastBullet{ 0.f };
		bool m_CanShoot{};
	};

}
