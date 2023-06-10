#pragma once
#include "BaseComponent.h"
#include "Observer.h"

#include <glm/vec2.hpp>
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

		virtual void Initialize(int health, glm::vec2 respawnPos, std::shared_ptr<GameObject> parent);
		virtual void Update() override;
		virtual void Render() const override;        

		void AddObserver(Observer* observer);
		void RemoveObserver(std::unique_ptr<Observer> observer);

		int GetHealth() const;
		void LoseHealth();

	private:
		int m_Health{};
		GameObject* m_Parent{ nullptr };
		GameObject* m_UI{ nullptr }; //UI the lives is displayed on, no UI --> nullptr

		void Notify(Observer::Event event);
		std::vector<Observer*> m_pObservers;

		glm::vec2 m_RespawnPos;
  	};
}

