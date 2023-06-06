#pragma once
#include "BaseComponent.h"

namespace dae
{
	class HealthComponent final : public BaseComponent
	{
	public:
		HealthComponent() = default;
		virtual ~HealthComponent() = default;
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		virtual void Initialize(int health, std::shared_ptr<GameObject> parent);
		virtual void Update() override;
		virtual void Render() const override;        

		int GetHealth() const;
		void LoseHealth(int amount);
	private:
		int m_Health{};
		GameObject* m_Parent{ nullptr };
  	};
}

