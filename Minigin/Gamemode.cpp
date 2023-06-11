#include "Gamemode.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::Gamemode::SetGameMode(Gamemode::GameModeEnum gameMode)
{
	m_GameMode = gameMode;
}

dae::Gamemode::GameModeEnum dae::Gamemode::GetGameMode() const
{
	return m_GameMode;
}

void dae::Gamemode::AddPlayer(std::shared_ptr<GameObject> player)
{
	m_Players.emplace_back(player);
}

void dae::Gamemode::PlayerDied(std::shared_ptr<GameObject> player)
{
	m_Players.erase(std::remove(m_Players.begin(), m_Players.end(), player), m_Players.end());
	if (m_Players.empty() && m_GameMode != dae::Gamemode::VERSUS)
	{
		std::cout << "Go to highscores\n";
	}
	if (m_GameMode == dae::Gamemode::VERSUS)
		std::cout << "Go to the next level\n";
}

std::vector<std::shared_ptr<dae::GameObject>> dae::Gamemode::GetPlayer() const
{
	return m_Players;
}

void dae::Gamemode::AddEnemy(std::shared_ptr<GameObject> player)
{
	m_Enemies.emplace_back(player);
}

void dae::Gamemode::EnemyDied(std::shared_ptr<GameObject> enemy)
{
	m_Enemies.erase(std::remove(m_Enemies.begin(), m_Enemies.end(), enemy), m_Enemies.end());
	if (m_Enemies.empty())
	{
		std::cout << "Go to the next level\n";
	}
}

std::vector<std::shared_ptr<dae::GameObject>> dae::Gamemode::GetEnemies() const
{
	return m_Enemies;
}
