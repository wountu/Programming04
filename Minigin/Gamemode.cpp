#include "Gamemode.h"
#include "Gamemode.h"
#include "SceneManager.h"
#include "Scene.h"
#include "LoadScenes.h"
#include "fstream"
#include "GameObject.h"
#include "MainPlayerPrefab.h"

void dae::Gamemode::HandleEvent(GameObject* parent, Event event)
{
	switch (event)
	{
	case dae::Observer::Event::Mainmenu_Picked:
		m_GameMode = parent->GetComponent<MainmenuComponent>()->GetMenu();
		StartGame();
		break;
	case dae::Observer::Event::Collectables_Pickedup:
		GoNextLevel();
		std::cout << "Load next level\n";
		break;
	}
}

void dae::Gamemode::OnSubjectDestroy()
{
}

void dae::Gamemode::Render() const
{
}

void dae::Gamemode::Update()
{
}

//void dae::Gamemode::SetGameMode(Gamemode::GameModeEnum gameMode)
//{
//	m_GameMode = gameMode;
//}
//
//dae::Gamemode::GameModeEnum dae::Gamemode::GetGameMode() const
//{
//	return m_GameMode;
//}

void dae::Gamemode::AddPlayer(std::shared_ptr<GameObject> player)
{
	m_Players.emplace_back(player);
	player->GetComponent<CollisionBoxComponent>()->SetActive(true);
}

void dae::Gamemode::PlayerDied(std::shared_ptr<GameObject> player)
{
	//m_ActivePlayers.erase(std::remove(m_ActivePlayers.begin(), m_ActivePlayers.end(), player), m_ActivePlayers.end());
	//if (m_ActivePlayers.empty() && m_GameMode != dae::Gamemode::VERSUS)
	//{
	//	GameDone();
	//}
	//if (m_GameMode == dae::Gamemode::VERSUS)
	//	GoNextLevel();
}

std::vector<std::shared_ptr<dae::GameObject>> dae::Gamemode::GetPlayer() const
{
	return m_Players;
}

void dae::Gamemode::AddEnemy(std::shared_ptr<GameObject> player)
{

}

void dae::Gamemode::EnemyDied(std::shared_ptr<GameObject> enemy)
{

}

std::vector<std::shared_ptr<dae::GameObject>> dae::Gamemode::GetEnemies() const
{
	return m_Enemies;
}

void dae::Gamemode::AddObserver(Observer* observer)
{
	m_pObservers.emplace_back(observer);
}

void dae::Gamemode::RemoveObserver(Observer* observer)
{
	m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), observer), m_pObservers.end());
}

void dae::Gamemode::StartGame()
{
	if (!m_GameStarted)
	{
		m_GameStarted = true;
		SceneManager::GetInstance().SetNextLevelActive();

		LoadPLayersAndEnemies(SceneManager::GetInstance().GetActiveScene()->GetLevelName());

	}
	
}

void dae::Gamemode::GoNextLevel()
{
	SceneManager::GetInstance().SetNextLevelActive();
	LoadPLayersAndEnemies(SceneManager::GetInstance().GetActiveScene()->GetLevelName());

	Notify(dae::Observer::Level_Next);

	//m_ActiveEnemies = m_Enemies;
	//m_ActivePlayers = m_Players;

	//++m_CurrentLevel;
	//if (m_CurrentLevel > 3)
	//{
	//	SceneManager::GetInstance().SetSceneByIdx(1);
	//	m_CurrentLevel = 1;

	//}
	//else SceneManager::GetInstance().SetNextLevelActive();

	//for (auto& enemy : m_Enemies)
	//{
	//	enemy->GetComponent<CollisionBoxComponent>()->SetActive(true);
	//}

	//for (auto& player : m_Players)
	//{
	//	player->GetComponent<CollisionBoxComponent>()->SetActive(true);
	//}

	//for (size_t idx{}; idx < m_Players.size(); ++idx)
	//{
	//	SceneManager::GetInstance().GetActiveScene()->Add(m_Players[idx]);
	//	m_Players[idx]->GetChildren()[0]->GetComponent<BulletManager>()->DestroyAllBullets();

	//	switch (m_CurrentLevel)
	//	{
	//		case 1:
	//			if(idx == 0)
	//				m_Players[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(80, 200));
	//			if(idx == 1)
	//				m_Players[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(42, 0));

	//			break;

	//		case 2:
	//			if (idx == 0)
	//				m_Players[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(80, 200));
	//			if (idx == 1)
	//				m_Players[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(42, 0));

	//			break;
	//		case 3:
	//			if (idx == 0)
	//				m_Players[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(80, 200));
	//			if (idx == 1)
	//				m_Players[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(42, 0));
	//	}
	//}

	//for (size_t idx{}; idx < m_Enemies.size(); ++idx)
	//{
	//	SceneManager::GetInstance().GetActiveScene()->Add(m_Enemies[idx]);
	//	m_Enemies[idx]->GetChildren()[0]->GetComponent<BulletManager>()->DestroyAllBullets();


	//	switch (m_CurrentLevel)
	//	{
	//	case 1:
	//		if (idx == 0)
	//		{
	//			m_Enemies[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(400, 390));
	//			m_Enemies[idx]->GetComponent<TransformComponent>()->SetDirection(glm::vec2{ -1, 0 });
	//			m_Enemies[idx]->GetComponent<AIComponent>()->Reset();
	//		}

	//		if (idx == 1)
	//		{
	//			m_Enemies[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(380, 16));
	//			m_Enemies[idx]->GetComponent<TransformComponent>()->SetDirection(glm::vec2{ 0, 1 });
	//			m_Enemies[idx]->GetComponent<AIComponent>()->Reset();
	//		}

	//		if (idx == 2)
	//		{
	//			m_Enemies[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(10, 350));
	//			m_Enemies[idx]->GetComponent<TransformComponent>()->SetDirection(glm::vec2{ 0, -1 });
	//			m_Enemies[idx]->GetComponent<AIComponent>()->Reset();
	//		}

	//		if (idx == 3)
	//		{
	//			m_Enemies[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(220, 155));
	//			m_Enemies[idx]->GetComponent<TransformComponent>()->SetDirection(glm::vec2{ 1, 0 });
	//			m_Enemies[idx]->GetComponent<AIComponent>()->Reset();
	//		}

	//		break;

	//	case 2:
	//		if (idx == 0)
	//		{
	//			m_Enemies[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(400, 390));
	//			m_Enemies[idx]->GetComponent<AIComponent>()->Reset();
	//		}

	//		if (idx == 1)
	//		{
	//			m_Enemies[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(200, 16));
	//			m_Enemies[idx]->GetComponent<TransformComponent>()->SetDirection({ 0, 1 });
	//			m_Enemies[idx]->GetComponent<AIComponent>()->Reset();
	//		}

	//		if (idx == 2)
	//		{
	//			m_Enemies[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(10, 300));
	//			m_Enemies[idx]->GetComponent<AIComponent>()->Reset();
	//		}

	//		if (idx == 3)
	//		{
	//			m_Enemies[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(230, 12));
	//			m_Enemies[idx]->GetComponent<TransformComponent>()->SetDirection({ 1,0 });
	//			m_Enemies[idx]->GetComponent<AIComponent>()->Reset();
	//		}

	//		break;
	//	case 3:
	//		if (idx == 0)
	//		{
	//			m_Enemies[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(400, 390));
	//			m_Enemies[idx]->GetComponent<AIComponent>()->Reset();
	//		}

	//		if (idx == 1)
	//		{
	//			m_Enemies[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(440, 10));
	//			m_Enemies[idx]->GetComponent<TransformComponent>()->SetDirection(glm::vec2{-1, 0});
	//			m_Enemies[idx]->GetComponent<AIComponent>()->Reset();
	//		}

	//		if (idx == 2)
	//		{
	//			m_Enemies[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(10, 350));
	//			m_Enemies[idx]->GetComponent<AIComponent>()->Reset();
	//		}

	//		if (idx == 3)
	//		{
	//			m_Enemies[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(65, 150));
	//			m_Enemies[idx]->GetComponent<TransformComponent>()->SetDirection({ 1,0 });
	//			m_Enemies[idx]->GetComponent<AIComponent>()->Reset();
	//		}

	//		break;
	//	}
	//}
}

void dae::Gamemode::GameDone()
{
	std::string pathName{ dae::ResourceManager::GetInstance().GetDataPath() + "HighScores.txt" };
	std::ifstream file(pathName);
	std::vector<int> highScores{};
	if (file.is_open())
	{
		std::string line{};
		while (std::getline(file, line))
		{
			int score = std::stoi(line);
			highScores.push_back(score);
		}

		for (const auto& player : m_Players)
		{
			int playerScore = player->GetComponent<ScoreComponent>()->GetScore();
			if (highScores.back() < playerScore)
			{
				highScores.pop_back();
				highScores.push_back(playerScore);
				std::sort(highScores.rbegin(), highScores.rend());
			}
		}
	}

	std::ofstream writeFile(pathName);
	if (writeFile.is_open())
	{
		for (int score : highScores)
		{
			writeFile << score << "\n";
		}
	}

	auto scene = SceneManager::GetInstance().CreateScene("Highscores");

	glm::vec2 startPos{ 250, 45 };

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	for (size_t idx{}; idx < highScores.size(); ++idx)
	{
		std::shared_ptr<GameObject> highScoresObj = std::make_shared<GameObject>();
		highScoresObj->Initialize();

		auto score = highScoresObj->AddComponent<TextObject>();

		score->Initialize(std::to_string(highScores[idx]), font, highScoresObj);
		score->SetPos({ startPos.x, startPos.y + (40 * idx) });


		scene->Add(highScoresObj);
	}


	SceneManager::GetInstance().SetActiveScene(scene);
}

void dae::Gamemode::LoadPLayersAndEnemies(std::string levelName)
{
	auto grid = dae::GridGenerator::GetInstance().GetGrid();
	auto scene = SceneManager::GetInstance().GetActiveScene();

	if (m_Player == nullptr)
	{
		CreatePlayer();
		AddObserver(m_Player->GetComponent<PlayerComponent>().get());
	}

	scene->Add(m_Player);
	m_Player->GetComponent<CollisionBoxComponent>()->SetActive(true);
	
	for (const auto& tile : grid[levelName])
	{
		if (tile.isSpawnPoint)
		{

			m_Player->GetComponent<dae::TransformComponent>()->ChangeLocalPosition(tile.LeftTop);
		}
	}
}

void dae::Gamemode::CreatePlayer()
{
	//Create the GO
	auto pacmanPrefab = std::make_unique<MainPlayerPrefab>();
	pacmanPrefab->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("pacman.png"));
	m_Player = pacmanPrefab->Create(glm::vec2(0, 0));

	//Observers
	auto scoreObserver = new dae::ScoreObserver(glm::vec2(475, 20), 0);
	m_Player->GetComponent<dae::ScoreComponent>()->AddObserver(scoreObserver);

	//Keybinds
	pacmanPrefab->SetMovementKeys(SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN);
	unsigned int idx = dae::InputManager::GetInstance().AddController();
	pacmanPrefab->SetMovementButtons(ControllerXbox::ControllerInputs::DPAD_LEFT, ControllerXbox::ControllerInputs::DPAD_RIGHT, ControllerXbox::ControllerInputs::DPAD_UP, ControllerXbox::ControllerInputs::DPAD_DOWN, idx);

}

void dae::Gamemode::Notify(Observer::Event event)
{
	for (const auto& observer : m_pObservers)
	{
		observer->HandleEvent(nullptr, event);
	}
}
