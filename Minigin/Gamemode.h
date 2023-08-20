#pragma once
#include "Singleton.h"
#include "GameObject.h"
#include "Observer.h"
#include "MainmenuComponent.h"
#include "HealthObserver.h"


#include <vector>
#include <memory>

namespace dae
{
	class Gamemode final : public Observer, public std::enable_shared_from_this<Gamemode>
	{
	public:
		enum GameModeEnum
		{
			MAIN_MENU,
			SINGLE_PLAYER,
			COOP,
			VERSUS
		};

		Gamemode() = default;
		virtual ~Gamemode() = default;
		Gamemode(const Gamemode& other) = delete;
		Gamemode& operator=(const Gamemode& other) = delete;
		Gamemode(Gamemode&& other) = delete;
		Gamemode& operator=(Gamemode&& other) = delete;

		virtual void HandleEvent(GameObject* actor, Event event) override;
		virtual void OnSubjectDestroy() override;

		virtual void Render() const override;
		virtual void Update() override;

		//void SetGameMode(GameModeEnum gameMode);
		//GameModeEnum GetGameMode() const;

		void AddPlayer(std::shared_ptr<GameObject> player);
		void PlayerDied(std::shared_ptr<GameObject> player);
		//std::vector<std::shared_ptr<GameObject>> GetPlayer() const;

		void AddEnemy(std::shared_ptr<GameObject> player);
		void EnemyDied(std::shared_ptr<GameObject> player);
		std::vector<std::shared_ptr<GameObject>> GetEnemies() const;

		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);

		void StartGame();
		void GoNextLevel();
		void ResetLevel();

		void GameDone();
	private:
		Menu m_GameMode{};
		//GameModeEnum m_GameMode{ };
		bool m_GameStarted{ false };
		void LoadPLayersAndEnemies(std::string levelName);

		void CreatePlayer();
		std::shared_ptr<dae::GameObject> m_Player{ nullptr };

		std::vector<std::shared_ptr<dae::GameObject>> m_Enemies{};
		void CreateEnemies();

		int m_CurrentLevel{};

		bool m_GameDone{};

		std::vector<Observer*> m_pObservers;
		void Notify(Observer::Event event);

		std::shared_ptr<dae::HealthObserver> m_HealthObs{ std::make_shared<dae::HealthObserver>(glm::vec2(475, 40), 3) };
	};

}

