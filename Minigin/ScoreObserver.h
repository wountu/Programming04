#pragma once
#include "ScoreObserver.h"
#include "TextObject.h"

namespace dae
{
	class ScoreObserver final : public Observer
	{
	public:
		ScoreObserver() = default;
		ScoreObserver(glm::vec2 pos, int score);
		~ScoreObserver() = default;

		ScoreObserver(const ScoreObserver& other) = delete;
		ScoreObserver& operator=(const ScoreObserver& other) = delete;
		ScoreObserver(ScoreObserver&& other) = delete;
		ScoreObserver& operator=(ScoreObserver&& other) = delete;

		void Initialize(glm::vec2 pos, int score);

		virtual void HandleEvent(GameObject* actor, Event event) override;
		virtual void OnSubjectDestroy() override;

		virtual void Render() const override;
		virtual void Update() override;
	private:
		std::string m_ScoreDisplay{};
		std::unique_ptr<TextObject> m_Text{ nullptr };
		int m_Score{};
	};
}

