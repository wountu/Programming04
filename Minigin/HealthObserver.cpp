#include "HealthObserver.h"
#include "GameObject.h"
#include "TextObject.h"
#include "ResourceManager.h"
#include "Gamemode.h"

#include <iostream>
#include <string>

dae::HealthObserver::HealthObserver(glm::vec2 pos, int startLives)
{
	m_Text = std::make_unique<TextObject>();

	m_LivesDisplay = "Health: " + std::to_string(startLives);
	m_Lives = startLives;

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	m_Text->Initialize(m_LivesDisplay, font, nullptr);
	m_Text->SetPos(pos);
}

void dae::HealthObserver::HandleEvent(GameObject*, Event event)
{
	switch (event)
	{
	case dae::Observer::Health_Lost:
		--m_Lives;
		m_LivesDisplay.back() = static_cast<char>(m_Lives + '0');
		m_Text->SetText(m_LivesDisplay);
		std::cout << "Lost health" << "\n";
		break;
	case dae::Observer::Health_Died:
		break;
	default:
		break;
	}
}

void dae::HealthObserver::OnSubjectDestroy()
{

}

void dae::HealthObserver::Render() const
{
	m_Text->Render();
}

void dae::HealthObserver::Update()
{
	m_Text->Update();
}
