#include "Gamemode.h"
#include "Gamemode.h"
#include "SceneManager.h"
#include "Scene.h"
#include "LoadScenes.h"
#include "fstream"
#include "GameObject.h"

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
	player->GetComponent<CollisionBoxComponent>()->SetActive(true);
}

void dae::Gamemode::PlayerDied(std::shared_ptr<GameObject> player)
{
	m_ActivePlayers.erase(std::remove(m_ActivePlayers.begin(), m_ActivePlayers.end(), player), m_ActivePlayers.end());
	if (m_ActivePlayers.empty() && m_GameMode != dae::Gamemode::VERSUS)
	{
		GameDone();
	}
	if (m_GameMode == dae::Gamemode::VERSUS)
		GoNextLevel();
}

std::vector<std::shared_ptr<dae::GameObject>> dae::Gamemode::GetPlayer() const
{
	return m_Players;
}

void dae::Gamemode::AddEnemy(std::shared_ptr<GameObject> player)
{
	m_Enemies.emplace_back(player);
	player->GetComponent<CollisionBoxComponent>()->SetActive(true);
}

void dae::Gamemode::EnemyDied(std::shared_ptr<GameObject> enemy)
{
	m_ActiveEnemies.erase(std::remove(m_ActiveEnemies.begin(), m_ActiveEnemies.end(), enemy), m_ActiveEnemies.end());
	if (m_ActiveEnemies.empty() && m_GameMode != dae::Gamemode::VERSUS)
	{
		GoNextLevel();
	}
}

std::vector<std::shared_ptr<dae::GameObject>> dae::Gamemode::GetEnemies() const
{
	return m_Enemies;
}

void dae::Gamemode::StartGame()
{
	if (!m_GameStarted)
	{
		m_ActivePlayers = m_Players;
		m_ActiveEnemies = m_Enemies;

		m_GameStarted = true;
		dae::SceneLoader::GetInstance().LoadScene1(m_GameMode);
		dae::SceneLoader::GetInstance().LoadScene2(m_GameMode);
		dae::SceneLoader::GetInstance().LoadScene3(m_GameMode);

		SceneManager::GetInstance().SetNextLevelActive();

		m_CurrentLevel = 1;

		LoadPLayersAndEnemies();
	}
	
}

void dae::Gamemode::GoNextLevel()
{
	m_ActiveEnemies = m_Enemies;
	m_ActivePlayers = m_Players;

	SceneManager::GetInstance().SetNextLevelActive();

	for (size_t idx{}; idx < m_Players.size(); ++idx)
	{
		SceneManager::GetInstance().GetActiveScene()->Add(m_Players[idx]);
		m_Players[idx]->GetChildren()[0]->GetComponent<BulletManager>()->DestroyAllBullets();

		switch (m_CurrentLevel)
		{
			case 1:
				if(idx == 0)
					m_Players[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(80, 200));
				if(idx == 1)
					m_Players[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(42, 0));

				break;

			case 2:
				if (idx == 0)
					m_Players[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(80, 200));
				if (idx == 1)
					m_Players[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(42, 0));

				break;
			case 3:
				if (idx == 0)
					m_Players[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(80, 200));
				if (idx == 1)
					m_Players[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(42, 0));
		}
	}

	for (size_t idx{}; idx < m_Enemies.size(); ++idx)
	{
		SceneManager::GetInstance().GetActiveScene()->Add(m_Enemies[idx]);
		m_Enemies[idx]->GetChildren()[0]->GetComponent<BulletManager>()->DestroyAllBullets();


		++m_CurrentLevel;
		if (m_CurrentLevel > 3)
		{
			SceneManager::GetInstance().SetSceneByIdx(1);
			m_CurrentLevel = 1;

		}

		switch (m_CurrentLevel)
		{
		case 1:
			if (idx == 0)
			{
				m_Enemies[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(400, 390));
				m_Enemies[idx]->GetComponent<AIComponent>()->Reset();
			}

			break;

		case 2:
			if (idx == 0)
			{
				m_Enemies[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(400, 390));
				m_Enemies[idx]->GetComponent<AIComponent>()->Reset();
			}

			break;
		case 3:
			if (idx == 0)
			{
				m_Enemies[idx]->GetComponent<TransformComponent>()->ChangeLocalPosition(glm::vec2(400, 390));
				m_Enemies[idx]->GetComponent<AIComponent>()->Reset();
			}

			break;
		}
	}
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

void dae::Gamemode::LoadPLayersAndEnemies()
{
	auto scene = SceneManager::GetInstance().GetActiveScene();

#pragma region TRONTANK01
		//TRONTANK01

		auto tronTank01 = std::make_shared <dae::GameObject>();
		auto healthTronTank01 = tronTank01->AddComponent<dae::HealthComponent>();
		auto scoreTronTank01 = tronTank01->AddComponent<dae::ScoreComponent>();
		auto renderCompTronTank01 = tronTank01->AddComponent<dae::RenderComponent>();
		auto transformTronTank01 = tronTank01->AddComponent <dae::TransformComponent>();

		auto tankCollision = tronTank01->AddComponent<dae::CollisionBoxComponent>();

		tronTank01->Initialize();
		auto texture = dae::ResourceManager::GetInstance().LoadTexture("BlueTank.png");
		renderCompTronTank01->Initialize(texture, tronTank01);
		transformTronTank01->Initialize(glm::vec2(80, 200), 180.f, tronTank01);
		healthTronTank01->Initialize(3, glm::vec2(80, 200), tronTank01);
		scoreTronTank01->Initialize(tronTank01);

		auto healthObserver = new dae::HealthObserver({ 500, 50 }, 3);
		healthTronTank01->AddObserver(healthObserver);

		auto scoreObserver = new dae::ScoreObserver({ 500, 65 }, 0);
		scoreTronTank01->AddObserver(scoreObserver);

		dae::CollisionBox box{};
		box._width = static_cast<float>(texture->GetSize().x);
		box._height = static_cast<float>(texture->GetSize().y);
		box._leftTop.x = transformTronTank01->GetLocalPosition().x;
		box._leftTop.y = transformTronTank01->GetLocalPosition().y;

		tankCollision->Initialize(tronTank01, box, 5);
		tronTank01->SetTag(dae::Player1);

		scene->Add(tronTank01);

		//Trontank aim
		auto aimTronTank01 = std::make_shared<dae::GameObject>();
		auto aimTransform = aimTronTank01->AddComponent<dae::TransformComponent>();
		auto bulletManager = aimTronTank01->AddComponent<dae::BulletManager>();
		auto renderCompAim = aimTronTank01->AddComponent<dae::RenderComponent>();

		aimTronTank01->Initialize();
		aimTransform->Initialize(glm::vec2{}, tronTank01->GetComponent<dae::TransformComponent>()->GetAngle(), aimTronTank01);
		bulletManager->Initialize(aimTronTank01);
		texture = dae::ResourceManager::GetInstance().LoadTexture("BlueTankGun.png");
		renderCompAim->Initialize(texture, aimTronTank01);

		aimTronTank01->SetParent(tronTank01, false);
		aimTronTank01->SetTag(dae::Player1);

		scene->Add(aimTronTank01);

		const float speed{ 100.f };
		auto& input = dae::InputManager::GetInstance();

		auto pCommand = input.AddCommand<dae::Movement>(tronTank01.get(), SDL_SCANCODE_W, dae::InputManager::KeyPress::HOLD);
		pCommand->SetDirectionAndSpeed(glm::vec2{ 0.f, -1.f }, speed);

		pCommand = input.AddCommand<dae::Movement>(tronTank01.get(), SDL_SCANCODE_S, dae::InputManager::KeyPress::HOLD);
		pCommand->SetDirectionAndSpeed(glm::vec2{ 0.f, 1.f }, speed);

		pCommand = input.AddCommand<dae::Movement>(tronTank01.get(), SDL_SCANCODE_A, dae::InputManager::KeyPress::HOLD);
		pCommand->SetDirectionAndSpeed(glm::vec2{ -1.f, 0.f }, speed);

		pCommand = input.AddCommand<dae::Movement>(tronTank01.get(), SDL_SCANCODE_D, dae::InputManager::KeyPress::HOLD);
		pCommand->SetDirectionAndSpeed(glm::vec2{ 1.f, 0.f }, speed);

		auto pShoot = input.AddCommand<dae::Shoot>(aimTronTank01.get(), SDL_SCANCODE_LEFT, dae::InputManager::KeyPress::SINGLEPRESS);
		pShoot->SetDirection(glm::vec2{ -1,0 });

		pShoot = input.AddCommand<dae::Shoot>(aimTronTank01.get(), SDL_SCANCODE_RIGHT, dae::InputManager::KeyPress::SINGLEPRESS);
		pShoot->SetDirection(glm::vec2{ 1,0 });

		pShoot = input.AddCommand<dae::Shoot>(aimTronTank01.get(), SDL_SCANCODE_UP, dae::InputManager::KeyPress::SINGLEPRESS);
		pShoot->SetDirection(glm::vec2{ 0,-1 });

		pShoot = input.AddCommand<dae::Shoot>(aimTronTank01.get(), SDL_SCANCODE_DOWN, dae::InputManager::KeyPress::SINGLEPRESS);
		pShoot->SetDirection(glm::vec2{ 0,1 });

		dae::Gamemode::GetInstance().AddPlayer(tronTank01);
#pragma endregion TRONTANK01

#pragma region TRONTANK02
	if (m_GameMode == dae::Gamemode::COOP)
	{
		unsigned controller = input.AddController();

		////TRONTANK 2
		auto tronTank02 = std::make_shared <dae::GameObject>();

		auto renderCompTronTank02 = tronTank02->AddComponent<dae::RenderComponent>();
		auto transformTronTank02 = tronTank02->AddComponent <dae::TransformComponent>();
		auto healthTronTank02 = tronTank02->AddComponent<dae::HealthComponent>();
		auto scoreTronTank02 = tronTank02->AddComponent<dae::ScoreComponent>();
		tankCollision = tronTank02->AddComponent<dae::CollisionBoxComponent>();

		tronTank02->Initialize();
		texture = dae::ResourceManager::GetInstance().LoadTexture("GreenTank.png");
		renderCompTronTank02->Initialize(texture, tronTank02);
		transformTronTank02->Initialize(glm::vec2(42, 0), 0.f, tronTank02);
		healthTronTank02->Initialize(3, glm::vec2(42, 0), tronTank02);
		scoreTronTank02->Initialize(tronTank02);

		auto healthObserver2 = new dae::HealthObserver({ 500, 100 }, 3);
		healthTronTank02->AddObserver(healthObserver2);

		auto scoreObserver2 = new dae::ScoreObserver({ 500, 115 }, 0);
		scoreTronTank02->AddObserver(scoreObserver2);

		box._width = static_cast<float>(texture->GetSize().x);
		box._height = static_cast<float>(texture->GetSize().y);
		box._leftTop = transformTronTank01->GetLocalPosition();

		tankCollision->Initialize(tronTank02, box, 5);
		tronTank02->SetTag(dae::Player2);

		scene->Add(tronTank02);
		dae::Gamemode::GetInstance().AddPlayer(tronTank02);

		//Trontank aim
		auto aimTronTank02 = std::make_shared<dae::GameObject>();
		auto aimTransform02 = aimTronTank02->AddComponent<dae::TransformComponent>();
		auto bulletManager02 = aimTronTank02->AddComponent<dae::BulletManager>();
		auto renderCompAim02 = aimTronTank02->AddComponent<dae::RenderComponent>();

		aimTronTank02->Initialize();
		aimTransform02->Initialize(glm::vec2{}, tronTank02->GetComponent<dae::TransformComponent>()->GetAngle(), aimTronTank02);
		bulletManager02->Initialize(aimTronTank02);
		texture = dae::ResourceManager::GetInstance().LoadTexture("GreenTankGun.png");
		renderCompAim02->Initialize(texture, aimTronTank02);

		aimTronTank02->SetParent(tronTank02, false);
		aimTronTank02->SetTag(dae::Player1);

		scene->Add(aimTronTank02);

		pCommand = input.AddCommand<dae::Movement>(controller, tronTank02.get(), ControllerXbox::ControllerInputs::DPAD_UP, dae::InputManager::KeyPress::HOLD);
		pCommand->SetDirectionAndSpeed(glm::vec2{ 0.f, -1.f }, speed); // - in y is up 

		pCommand = input.AddCommand<dae::Movement>(controller, tronTank02.get(), ControllerXbox::ControllerInputs::DPAD_DOWN, dae::InputManager::KeyPress::HOLD);
		pCommand->SetDirectionAndSpeed(glm::vec2{ 0.f, 1.f }, speed);

		pCommand = input.AddCommand<dae::Movement>(controller, tronTank02.get(), ControllerXbox::ControllerInputs::DPAD_LEFT, dae::InputManager::KeyPress::HOLD);
		pCommand->SetDirectionAndSpeed(glm::vec2{ -1.f, 0.f }, speed);

		pCommand = input.AddCommand<dae::Movement>(controller, tronTank02.get(), ControllerXbox::ControllerInputs::DPAD_RIGHT, dae::InputManager::KeyPress::HOLD);
		pCommand->SetDirectionAndSpeed(glm::vec2{ 1.f, 0.f }, speed);

		pShoot = input.AddCommand<dae::Shoot>(controller, aimTronTank02.get(), ControllerXbox::ControllerInputs::X, dae::InputManager::KeyPress::SINGLEPRESS);
		pShoot->SetDirection(glm::vec2{ -1,0 });

		pShoot = input.AddCommand<dae::Shoot>(controller, aimTronTank02.get(), ControllerXbox::ControllerInputs::B, dae::InputManager::KeyPress::SINGLEPRESS);
		pShoot->SetDirection(glm::vec2{ 1,0 });

		pShoot = input.AddCommand<dae::Shoot>(controller, aimTronTank02.get(), ControllerXbox::ControllerInputs::Y, dae::InputManager::KeyPress::SINGLEPRESS);
		pShoot->SetDirection(glm::vec2{ 0,-1 });

		pShoot = input.AddCommand<dae::Shoot>(controller, aimTronTank02.get(), ControllerXbox::ControllerInputs::A, dae::InputManager::KeyPress::SINGLEPRESS);
		pShoot->SetDirection(glm::vec2{ 0,1 });
	}
#pragma endregion TRONTANK02

#pragma region AI
	if (m_GameMode != dae::Gamemode::VERSUS)
	{
		//AI
		const auto aiTexture = dae::ResourceManager::GetInstance().LoadTexture("GreenTank.png");

		auto aiTank01 = std::make_shared <dae::GameObject>();
		auto transformAITank01 = aiTank01->AddComponent <dae::TransformComponent>();
		auto renderCompAITank01 = aiTank01->AddComponent<dae::RenderComponent>();
		auto healthAITank01 = aiTank01->AddComponent<dae::HealthComponent>();
		auto AI1TankCollision = aiTank01->AddComponent<dae::CollisionBoxComponent>();
		auto visionAi1 = aiTank01->AddComponent<dae::VisionComponent>();

		aiTank01->Initialize();
		aiTank01->SetTag(dae::AI);
		transformAITank01->Initialize(glm::vec2(400, 390), 0.f, aiTank01);
		transformAITank01->SetDirection(glm::vec2{ -1, 0 });
		renderCompAITank01->Initialize(aiTexture, aiTank01);
		healthAITank01->Initialize(0, glm::vec2(400, 390), aiTank01);

		box._width = static_cast<float>(aiTexture->GetSize().x);
		box._height = static_cast<float>(aiTexture->GetSize().y);
		box._leftTop.x = transformTronTank01->GetLocalPosition().x;
		box._leftTop.y = transformTronTank01->GetLocalPosition().y;

		AI1TankCollision->Initialize(aiTank01, box, 5);
		visionAi1->Initialize(aiTank01, 500, { aiTexture->GetSize().x / 2, aiTexture->GetSize().y / 2 });


		//Aim
		auto aimAI01 = std::make_shared<dae::GameObject>();
		auto aimTransformAI01 = aimAI01->AddComponent<dae::TransformComponent>();
		auto renderCompAimAI01 = aimAI01->AddComponent<dae::RenderComponent>();
		auto bulletManagerAI01 = aimAI01->AddComponent<dae::BulletManager>();

		aimAI01->Initialize();
		aimAI01->SetParent(aiTank01, false);
		aimAI01->SetTag(dae::AI);
		aimTransformAI01->Initialize(glm::vec2{}, aiTank01->GetComponent<dae::TransformComponent>()->GetAngle(), aimAI01);
		texture = dae::ResourceManager::GetInstance().LoadTexture("GreenTankGun.png");
		renderCompAimAI01->Initialize(texture, aimAI01);
		bulletManagerAI01->Initialize(aimAI01);

		auto ai01 = aiTank01->AddComponent<dae::AIComponent>();
		ai01->Initialize(speed / 2.f, aiTank01, bulletManagerAI01);


		scene->Add(aimAI01);
		scene->Add(aiTank01);

		dae::Gamemode::GetInstance().AddEnemy(aiTank01);
	}
#pragma endregion AI


}
