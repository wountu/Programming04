#pragma once
#include "Singleton.h"
#include "GameObject.h"

#include <vector>
namespace dae
{
	class Gamemode final : public Singleton<Gamemode>
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

		void SetGameMode(GameModeEnum gameMode);
		GameModeEnum GetGameMode() const;

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
		GameModeEnum m_GameMode{ };
		bool m_GameStarted{ false };

		std::vector<std::shared_ptr<GameObject>> m_Players;
		std::vector<std::shared_ptr<GameObject>> m_ActivePlayers;
		std::vector<std::shared_ptr<GameObject>> m_Enemies;
		std::vector<std::shared_ptr<GameObject>> m_ActiveEnemies;

		void LoadPLayersAndEnemies();
		int m_CurrentLevel{};

		bool m_GameDone{};
	};

}

