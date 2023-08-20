#include "ScoreObserver.h"
#include "ResourceManager.h"
#include "ScoreComponent.h"

#include <string>

dae::ScoreObserver::ScoreObserver(glm::vec2 pos, int score)
{
	m_Text = std::make_unique<TextObject>();

	m_ScoreDisplay = "Score: " + std::to_string(score);
	m_Score = score;

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	m_Text->Initialize(m_ScoreDisplay, font, nullptr);
	m_Text->SetPos(pos);
}

void dae::ScoreObserver::Initialize(glm::vec2 pos, int score)
{
	m_Text = std::make_unique<TextObject>();

	m_ScoreDisplay = "Score: " + std::to_string(score);
	m_Score = score;

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	m_Text->Initialize(m_ScoreDisplay, font, nullptr);
	m_Text->SetPos(pos);
}

void dae::ScoreObserver::HandleEvent(GameObject* actor, Event event)
{
	switch (event)
	{
	case dae::Observer::Score_Add:
		auto scoreComp = actor->GetComponent<ScoreComponent>();
		if (scoreComp)
		{
			int score = scoreComp->GetScore();
			m_Score = score;
			m_ScoreDisplay = std::string{ "Score: " + std::to_string(score) };
			m_Text->SetText(m_ScoreDisplay);
		}
		break;
	}
}

void dae::ScoreObserver::OnSubjectDestroy()
{
}

void dae::ScoreObserver::Render() const
{
	m_Text->Render();
}

void dae::ScoreObserver::Update()
{
	m_Text->Update();
}
