#pragma once
#include "BaseComponent.h"
#include "Observer.h"

#include <vector>

namespace dae
{
	class ScoreComponent final : public BaseComponent
	{
	public:
		ScoreComponent() = default;
		virtual ~ScoreComponent();
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		virtual void Initialize(std::shared_ptr<GameObject> parent, int startScore = 0);
		virtual void Update() override;
		virtual void Render() const override;

		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);

		int GetScore() const;
		void AddScore(int score);
	private:
		int m_Score{};
		GameObject* m_Parent{ nullptr };

		std::vector<Observer*> m_pObservers;

		void Notify(Observer::Event event);
	};
}
