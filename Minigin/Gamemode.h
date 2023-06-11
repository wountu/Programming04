#pragma once
#include "Singleton.h"
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
	private:
		GameModeEnum m_GameMode{ };
	};

}

