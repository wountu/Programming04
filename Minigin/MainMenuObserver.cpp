#include "MainMenuObserver.h"
#include "ResourceManager.h"
#include "MainmenuComponent.h"

void dae::MainMenuObserver::Initialize(glm::vec2 pos, std::string startText)
{
	m_Text = std::make_unique<TextObject>();

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	m_Text->Initialize(startText, font, nullptr);
	m_Text->SetPos(pos);
}

void dae::MainMenuObserver::HandleEvent(GameObject* parent, Event event)
{
	if (event == dae::Observer::Mainmenu_Changed)
	{
		auto mainMenuComp = parent->GetComponent<MainmenuComponent>();
		m_Text->SetText(mainMenuComp->GetMenuText());
	}
}

void dae::MainMenuObserver::OnSubjectDestroy()
{
}

void dae::MainMenuObserver::Render() const
{
	m_Text->Render();
}

void dae::MainMenuObserver::Update()
{
	m_Text->Update();
}
