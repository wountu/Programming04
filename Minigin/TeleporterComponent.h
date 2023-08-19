#pragma once
#include "BaseComponent.h"
#include "CollisionBoxComponent.h"

namespace dae
{
	class TeleporterComponent final : public BaseComponent
	{
	public:
		TeleporterComponent() = default;
		virtual ~TeleporterComponent() = default;

		TeleporterComponent(const TeleporterComponent& other) = delete;
		TeleporterComponent operator=(const TeleporterComponent& other) = delete;
		TeleporterComponent(TeleporterComponent&& other) = delete;
		TeleporterComponent operator=(TeleporterComponent&& other) = delete;

		void Initialize(std::shared_ptr<GameObject> parent);

		virtual void Render() const;
		virtual void Update();

		glm::vec2 GetPosition() const;

		void LinkToOtherTeleporter(std::shared_ptr<TeleporterComponent> teleporter);
		void Teleported(GameObject* object);

		bool IsColliding() const;
	private:
		GameObject* m_Parent{ nullptr };
		TeleporterComponent* m_OtherTeleporter{ nullptr };
		CollisionBoxComponent* m_Collision{ nullptr };

		GameObject* m_TeleportedObj{ nullptr };

		bool m_IsColliding{};
	};
}

