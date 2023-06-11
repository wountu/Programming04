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

	private:
		GameModeEnum m_GameMode{ };

		std::vector<std::shared_ptr<GameObject>> m_Players;
		std::vector<std::shared_ptr<GameObject>> m_Enemies;
	};

}

