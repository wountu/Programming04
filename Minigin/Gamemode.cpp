#include "Gamemode.h"

void dae::Gamemode::SetGameMode(Gamemode::GameModeEnum gameMode)
{
	m_GameMode = gameMode;
}

dae::Gamemode::GameModeEnum dae::Gamemode::GetGameMode() const
{
	return m_GameMode;
}
