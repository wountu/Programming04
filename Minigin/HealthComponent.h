#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include <vector>

namespace dae
{
	class HealthComponent final : public BaseComponent
	{
	public:
		HealthComponent() = default;
		virtual ~HealthComponent();
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		virtual void Initialize(int health, std::shared_ptr<GameObject> parent);
		virtual void Update() override;
		virtual void Render() const override;        

		void AddObserver(Observer* observer);
		void RemoveObserver(std::unique_ptr<Observer> observer);
		void Notify(Observer::Event event);

		int GetHealth() const;
		void LoseHealth(int amount);
	private:
		int m_Health{};
		GameObject* m_Parent{ nullptr };
		GameObject* m_UI{ nullptr }; //UI the lives is displayed on, no UI --> nullptr

		std::vector<Observer*> m_pObservers;
  	};
}

