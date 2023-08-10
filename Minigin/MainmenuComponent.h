#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "Command.h"
#include <vector>
#include <string>

namespace dae
{
	enum class Menu
	{
		SINGLE,
		COOP,
		VERSUS
	};

	class MainmenuComponent final : public BaseComponent
	{
	public:
		MainmenuComponent() = default;
		virtual ~MainmenuComponent() = default;

		MainmenuComponent(const MainmenuComponent& other) = delete;
		MainmenuComponent operator=(const MainmenuComponent& other) = delete;
		MainmenuComponent(MainmenuComponent&& other) = delete;
		MainmenuComponent operator=(MainmenuComponent&& other) = delete;

		void Initialize(std::shared_ptr<GameObject> parent, Menu start);

		virtual void Render() const;
		virtual void Update();

		void GoNext();
		void GoPrevious();
		void StartGame();

		void AddObserver(std::shared_ptr<Observer> observer);
		void RemoveObserver(std::shared_ptr<Observer> observer);

		std::string GetMenuText() const;

	private:
		void DisableCommands();

		Menu m_CurrentMenu;
		std::vector<std::shared_ptr<Observer>> m_Observers;
		GameObject* m_Parent{};

		NextGamemode* m_NextGameModeCommand{};
		PreviousGamemode* m_PreviousGameModeCommand{};
		Start* m_StartGameCommand{};
	};
}

