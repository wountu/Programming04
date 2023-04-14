#include "ScoreDisplayObserver.h"
#include <iostream>

dae::ScoreDisplayObserver::ScoreDisplayObserver(std::shared_ptr<GameObject> parent, glm::vec2 pos)
{
	m_Parent = parent.get();
	m_Position = pos;

	m_pTextObject = m_Parent->GetComponent<TextObject>();
	m_pScoreComp = m_Parent->GetComponent<ScoreComponent>();
	m_Score = m_pScoreComp->GetScore();
}

void dae::ScoreDisplayObserver::Notify(GameObject* , Event event)
{
	if (event == Event::SCORE_ADDED)
	{
		m_pTextObject->SetText(std::string("Score: " + std::to_string(m_pScoreComp->GetScore())));
		std::cout << "Score changed!" << "\n";
	}
}

void dae::ScoreDisplayObserver::Update()
{

}

void dae::ScoreDisplayObserver::Render() const
{
}
