#include "MainmenuComponent.h"
#include "InputManager.h"
#include "ControllerXbox.h"
//#include "SDL.h"

void dae::MainmenuComponent::Initialize(std::shared_ptr<GameObject> parent, Menu start)
{
	m_Parent = parent.get();
	m_CurrentMenu = start;

	auto& input = dae::InputManager::GetInstance();
	m_NextGameModeCommand = input.AddCommand<dae::NextGamemode>(parent.get(), SDL_SCANCODE_RIGHT, dae::InputManager::KeyPress::SINGLEPRESS);
	m_PreviousGameModeCommand = input.AddCommand<dae::PreviousGamemode>(parent.get(), SDL_SCANCODE_LEFT, dae::InputManager::KeyPress::SINGLEPRESS);
	m_StartGameCommand = input.AddCommand <dae::Start>(parent.get(), SDL_SCANCODE_RETURN, dae::InputManager::KeyPress::SINGLEPRESS);
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

void dae::MainmenuComponent::DisableCommands()
{
	auto& input = InputManager::GetInstance();
	input.RemoveCommand(m_NextGameModeCommand);
	input.RemoveCommand(m_PreviousGameModeCommand);
	input.RemoveCommand(m_StartGameCommand);
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
	if (newMenu < 0)
		newMenu = 2;

	m_CurrentMenu = static_cast<Menu>(newMenu);

	for (const auto& observer : m_Observers)
		observer->HandleEvent(m_Parent, Observer::Mainmenu_Changed);
}

void dae::MainmenuComponent::StartGame()
{
	DisableCommands();
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
		return "SINGLE PLAYER";
	}
}

