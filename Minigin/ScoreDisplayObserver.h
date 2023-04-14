#pragma once
#include "Observer.h"
#include "glm/vec2.hpp"
#include "TextObject.h"
#include "ScoreComponent.h"
#include <memory>

namespace dae
{
	class ScoreDisplayObserver final : public Observer
	{
	public:
		ScoreDisplayObserver(std::shared_ptr<GameObject> parent, int startScore = 0);
		virtual ~ScoreDisplayObserver() = default;

		ScoreDisplayObserver(const ScoreDisplayObserver& other) = delete;
		ScoreDisplayObserver& operator=(const ScoreDisplayObserver& other) = delete;
		ScoreDisplayObserver(ScoreDisplayObserver&& other) = delete;
		ScoreDisplayObserver& operator=(ScoreDisplayObserver&& other) = delete;

		virtual void Notify(GameObject* actor, Event event);
		virtual void Update();
		virtual void Render() const;
	private:
		int m_Score{};
		GameObject* m_Parent{ nullptr };

		std::shared_ptr<ScoreComponent> m_pScoreComp{ nullptr };
		std::shared_ptr<TextObject> m_pTextObject{ nullptr };
	};
}


