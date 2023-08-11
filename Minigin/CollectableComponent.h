#pragma once
#include "BaseComponent.h"
#include "glm/vec2.hpp"
#include "CollisionBoxComponent.h"
#include "Observer.h"
#include <vector>

namespace dae
{
	class CollectableComponent final : public BaseComponent
	{
	public:
		CollectableComponent() = default;
		virtual ~CollectableComponent();
		CollectableComponent(const CollectableComponent& other) = delete;
		CollectableComponent& operator=(const CollectableComponent& other) = delete;
		CollectableComponent(CollectableComponent&& other) = delete;
		CollectableComponent& operator=(CollectableComponent&& other) = delete;

		virtual void Initialize(std::shared_ptr<GameObject> parent, int collectableScore);
		virtual void Update() override;

		void AddObserver(std::shared_ptr<Observer> observer);
		void RemoveObserver(std::shared_ptr<Observer> observer);
	private:
		void PickUp(GameObject* overlap);

		CollisionBoxComponent* m_CollisionBox{};
		GameObject* m_Parent{};
		int m_CollectableScore{};

		std::vector<std::shared_ptr<Observer>> m_Observers{};
		void Notify(Observer::Event event);
	};
}
