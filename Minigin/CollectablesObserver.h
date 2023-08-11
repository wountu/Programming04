#pragma once
#include "Observer.h"

#include <vector>
#include <memory>

namespace dae
{
	class CollectablesObserver final : public Observer
	{
	public:
		CollectablesObserver() = default;
		~CollectablesObserver() = default;

		CollectablesObserver(const CollectablesObserver& other) = delete;
		CollectablesObserver& operator=(const CollectablesObserver& other) = delete;
		CollectablesObserver(CollectablesObserver&& other) = delete;
		CollectablesObserver& operator=(CollectablesObserver&& other) = delete;

		virtual void HandleEvent(GameObject* actor, Event event) override;
		virtual void OnSubjectDestroy() override;

		virtual void Render() const override;
		virtual void Update() override;

		void AddObserver(std::shared_ptr<Observer> observer);
		void RemoveObserver(std::shared_ptr<Observer> observer);
	private:
		int m_Collectables{};
		std::vector<std::shared_ptr<Observer>> m_Observers;

		void Notify(Observer::Event event);
	};
}

