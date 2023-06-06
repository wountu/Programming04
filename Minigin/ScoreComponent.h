#pragma once
#include "BaseComponent.h"

namespace dae
{
	class ScoreComponent final : public BaseComponent
	{
	public:
		ScoreComponent() = default;
		virtual ~ScoreComponent() = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		virtual void Initialize(std::shared_ptr<GameObject> parent, int startScore = 0);
		virtual void Update() override;
		virtual void Render() const override;

		int GetScore() const;
		void AddScore(int score);
	private:
		int m_Score{};
		GameObject* m_Parent{ nullptr };
	};
}
