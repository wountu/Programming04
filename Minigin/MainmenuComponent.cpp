#include "MainmenuComponent.h"

void dae::MainmenuComponent::Initialize(std::shared_ptr<GameObject> parent, Menu start)
{
	m_Parent = parent.get();
	m_CurrentMenu = start;
}

void dae::MainmenuComponent::Render() const
{
	for (const auto& observer : m_Observers)
		observer->Render();
}

void dae::MainmenuComponent::Update()
{
	for (const auto& observer : m_Observers)
		observer->Update();
}

void dae::MainmenuComponent::GoNext()
{
	int newMenu = static_cast<int>(m_CurrentMenu) + 1;
	newMenu %= 3;

	m_CurrentMenu = static_cast<Menu>(newMenu);

	for (const auto& observer : m_Observers)
		observer->HandleEvent(m_Parent, Observer::Mainmenu_Changed);
}

void dae::MainmenuComponent::GoPrevious()
{
	int newMenu = static_cast<int>(m_CurrentMenu) - 1;
	newMenu %= 3;
}

void dae::MainmenuComponent::AddObserver(std::shared_ptr<Observer> observer)
{
	m_Observers.emplace_back(observer);
}

void dae::MainmenuComponent::RemoveObserver(std::shared_ptr<Observer> observer)
{
	m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer));
}

std::string dae::MainmenuComponent::GetMenuText() const
{
	switch (m_CurrentMenu)
	{
	case Menu::SINGLE:
		return "SINGLE PLAYER";
		break;
	case Menu::COOP:
		return "COOP";
		break;
	case Menu::VERSUS:
		return "VERSUS";
		break;
	default :
		return "SINGLE";
	}
}

