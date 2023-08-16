#pragma once
#include "Singleton.h"
#include "GameObject.h"
#include "Observer.h"
#include "MainmenuComponent.h"

#include <vector>

namespace dae
{
	class Gamemode final : public Observer
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
		std::vector<std::shared_ptr<GameObject>> GetPlayer() const;

		void AddEnemy(std::shared_ptr<GameObject> player);
		void EnemyDied(std::shared_ptr<GameObject> player);
		std::vector<std::shared_ptr<GameObject>> GetEnemies() const;

		void StartGame();
		void GoNextLevel();

		void GameDone();
	private:
		Menu m_GameMode{};
		//GameModeEnum m_GameMode{ };
		bool m_GameStarted{ false };

		std::vector<std::shared_ptr<GameObject>> m_Players;
		std::vector<std::shared_ptr<GameObject>> m_ActivePlayers;
		std::vector<std::shared_ptr<GameObject>> m_Enemies;
		std::vector<std::shared_ptr<GameObject>> m_ActiveEnemies;

		void LoadPLayersAndEnemies(std::string levelName);
		int m_CurrentLevel{};

		bool m_GameDone{};
	};

}

