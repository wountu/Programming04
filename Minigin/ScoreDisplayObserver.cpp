#include "ScoreDisplayObserver.h"
#include <iostream>

dae::ScoreDisplayObserver::ScoreDisplayObserver(std::shared_ptr<GameObject> parent, int startScore)
{
	m_Parent = parent.get();

	m_pTextObject = m_Parent->GetComponent<TextObject>();
	m_pTextObject->SetText("Score: " + std::to_string(startScore));
}

void dae::ScoreDisplayObserver::Notify(GameObject* actor, Event event)
{
	//Check if the event is receiving damage and if the actor that received dmg is the parent of the observer
	if (event == Event::SCORE_ADDED && actor == m_Parent->GetParent())
	{
		const int score = actor->GetComponent<ScoreComponent>()->GetScore();
		m_pTextObject->SetText(std::string("Score: " + std::to_string(score)));
		std::cout << "Score changed!" << "\n";
	}
}

void dae::ScoreDisplayObserver::Update()
{

}

void dae::ScoreDisplayObserver::Render() const
{
}
