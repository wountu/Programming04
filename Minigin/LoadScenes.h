#pragma once
#include "Gamemode.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "LevelGenerator.h"
#include "RenderComponent.h"
#include "Scene.h"
#include "Command.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "HealthObserver.h"
#include "ScoreObserver.h"
#include "Texture2D.h"
#include "BulletManager.h"
#include "InputManager.h"
#include "fpsCounter.h"
#include "AIComonent.h"
#include "VisionComponent.h"
#include "Singleton.h"
#include "LevelGenerator.h"
#include "SceneManager.h"
#include "Gamemode.h"
#include "Scene.h"
#include "DotsPrefab.h"
#include <memory>

namespace dae
{
	class LevelLoader final : public Singleton<LevelLoader>
	{
	public:
		LevelLoader() = default;

		void LoadLevel(std::string level, std::shared_ptr<dae::Gamemode> gameMode, std::string levelName)
		{
			auto& sceneManager = dae::SceneManager::GetInstance();
			auto scene = sceneManager.CreateScene(levelName);

			auto& resourceMan = dae::ResourceManager::GetInstance();
			auto& gridGen = dae::GridGenerator::GetInstance();

			auto pathTexture = resourceMan.LoadTexture("path.png");
			auto wallTexture = resourceMan.LoadTexture("wall.png");

			gridGen.LinkTextureToTile(dae::TileType::PATH, pathTexture);
			gridGen.LinkTextureToTile(dae::TileType::WALL, wallTexture);
			gridGen.SetTileDimensions(pathTexture->GetSize());

			GridGenerator::Grid grid = gridGen.CreateGrid(level, glm::vec2(pathTexture->GetSize().x, pathTexture->GetSize().y), levelName);
			scene->Add(gridGen.CreateGameObjects(levelName));

			auto collectableObserver = std::make_shared<dae::CollectablesObserver>();

			collectableObserver->AddObserver(gameMode);

			for (const auto& tile :	grid[levelName])
			{
				if (tile.hasDot)
				{
					auto dotPrefab = std::make_unique<DotsPrefab>();
					dotPrefab->SetTexture(resourceMan.LoadTexture("pill.png"));
					dotPrefab->SetDotScore(10);
					dotPrefab->SetDotObserver(collectableObserver);
					scene->Add(dotPrefab->Create(tile.LeftTop));
				}

				if (tile.hasBigDot)
				{
					auto dotPrefab = std::make_unique<DotsPrefab>();
					dotPrefab->SetTexture(resourceMan.LoadTexture("boost.png"));
					dotPrefab->SetDotScore(50);
					dotPrefab->SetDotObserver(collectableObserver);
					scene->Add(dotPrefab->Create(tile.LeftTop));
				}
			}
		}
	};


	/*void CreateLevel(Scene* pScene, LevelData* pLevelData)
	{
		auto pathWayTexture = dae::ResourceManager::GetInstance().LoadTexture("Level/Textures/path.png");
		auto wallTexture = dae::ResourceManager::GetInstance().LoadTexture("level/Textures/wall.png");
		auto voidTexture = dae::ResourceManager::GetInstance().LoadTexture("level/Textures/void.png");

		for (const auto& pathWay : pLevelData->pathWays)
		{
			auto block = std::make_shared<dae::GameObject>();
			auto render = block->AddComponent<dae::RenderComponent>();
			auto transform = block->AddComponent<dae::TransformComponent>();

			block->Initialize();
			transform->Initialize(pathWay.LeftTop, 0.f, block);
			render->Initialize(pathWayTexture, block);


			pScene->Add(block);
		}

		for (const auto& wall : pLevelData->walls)
		{
			auto block = std::make_shared<dae::GameObject>();
			auto render = block->AddComponent<dae::RenderComponent>();
			auto transform = block->AddComponent<dae::TransformComponent>();
			auto collison = block->AddComponent<dae::CollisionBoxComponent>();

			dae::CollisionBox colBox;
			colBox._leftTop = wall.LeftTop;
			colBox._height = static_cast<float>(wall.Height);
			colBox._width = static_cast<float>(wall.Width);

			collison->Initialize(block, colBox, 0);
			block->Initialize();
			transform->Initialize(wall.LeftTop, 0.f, block);
			render->Initialize(wallTexture, block);




			pScene->Add(block);
		}

		for (const auto& activeVoid : pLevelData->Void)
		{
			auto block = std::make_shared<dae::GameObject>();
			auto render = block->AddComponent<dae::RenderComponent>();
			auto transform = block->AddComponent<dae::TransformComponent>();

			block->Initialize();
			transform->Initialize(activeVoid.LeftTop, 0.f, block);
			render->Initialize(voidTexture, block);

			pScene->Add(block);
		}
	}*/

	//class SceneLoader final : public Singleton<SceneLoader>
	//{
	//public:
	//	SceneLoader() = default;
	//	virtual ~SceneLoader() = default;
	//	SceneLoader(const SceneLoader& other) = delete;
	//	SceneLoader& operator=(const SceneLoader& other) = delete;
	//	SceneLoader(Gamemode&& other) = delete;
	//	SceneLoader& operator=(SceneLoader&& other) = delete;

	//	/*void LoadLevel(Scene* pScene, LevelData* pLevelData)
	//	{
	//		auto pathWayTexture = dae::ResourceManager::GetInstance().LoadTexture("Level/Textures/path.png");
	//		auto wallTexture = dae::ResourceManager::GetInstance().LoadTexture("level/Textures/wall.png");
	//		auto voidTexture = dae::ResourceManager::GetInstance().LoadTexture("level/Textures/void.png");

	//		for (const auto& pathWay : pLevelData->pathWays)
	//		{
	//			auto block = std::make_shared<dae::GameObject>();
	//			auto render = block->AddComponent<dae::RenderComponent>();
	//			auto transform = block->AddComponent<dae::TransformComponent>();

	//			block->Initialize();
	//			transform->Initialize(pathWay.LeftTop, 0.f, block);
	//			render->Initialize(pathWayTexture, block);

	//			
	//			pScene->Add(block);
	//		}

	//		for (const auto& wall : pLevelData->walls)
	//		{
	//			auto block = std::make_shared<dae::GameObject>();
	//			auto render = block->AddComponent<dae::RenderComponent>();
	//			auto transform = block->AddComponent<dae::TransformComponent>();
	//			auto collison = block->AddComponent<dae::CollisionBoxComponent>();

	//			dae::CollisionBox colBox;
	//			colBox._leftTop = wall.LeftTop;
	//			colBox._height = static_cast<float>(wall.Height);
	//			colBox._width = static_cast<float>(wall.Width);

	//			collison->Initialize(block, colBox, 0);
	//			block->Initialize();
	//			transform->Initialize(wall.LeftTop, 0.f, block);
	//			render->Initialize(wallTexture, block);




	//			pScene->Add(block);
	//		}

	//		for (const auto& activeVoid : pLevelData->Void)
	//		{
	//			auto block = std::make_shared<dae::GameObject>();
	//			auto render = block->AddComponent<dae::RenderComponent>();
	//			auto transform = block->AddComponent<dae::TransformComponent>();

	//			block->Initialize();
	//			transform->Initialize(activeVoid.LeftTop, 0.f, block);
	//			render->Initialize(voidTexture, block);

	//			pScene->Add(block);
	//		}
	//	}*/

	//	void LoadScene1()
	//	{
	//		auto pathWayTexture = dae::ResourceManager::GetInstance().LoadTexture("Level/Textures/path.png");
	//		auto wallTexture = dae::ResourceManager::GetInstance().LoadTexture("level/Textures/wall.png");
	//		auto voidTexture = dae::ResourceManager::GetInstance().LoadTexture("level/Textures/void.png");

	//		static const auto scene = dae::SceneManager::GetInstance().CreateScene("1st scene");

	//		auto& level = dae::LevelGenerator::GetInstance();
	//		std::unique_ptr<LevelData> pLevelData = level.LoadLevel("Level/LevelLayout0.csv");

	//		for (const auto& pathWay : pLevelData->pathWays)
	//		{
	//			auto block = std::make_shared<dae::GameObject>();
	//			auto render = block->AddComponent<dae::RenderComponent>();
	//			auto transform = block->AddComponent<dae::TransformComponent>();

	//			block->Initialize();
	//			transform->Initialize(pathWay.LeftTop, 0.f, block);
	//			render->Initialize(pathWayTexture, block);


	//			scene->Add(block);
	//		}

	//		for (const auto& wall : pLevelData->walls)
	//		{
	//			auto block = std::make_shared<dae::GameObject>();
	//			auto render = block->AddComponent<dae::RenderComponent>();
	//			auto transform = block->AddComponent<dae::TransformComponent>();
	//			auto collison = block->AddComponent<dae::CollisionBoxComponent>();

	//			dae::CollisionBox colBox;
	//			colBox._leftTop = wall.LeftTop;
	//			colBox._height = static_cast<float>(wall.Height);
	//			colBox._width = static_cast<float>(wall.Width);

	//			collison->Initialize(block, colBox, 0);
	//			block->Initialize();
	//			transform->Initialize(wall.LeftTop, 0.f, block);
	//			render->Initialize(wallTexture, block);




	//			scene->Add(block);
	//		}

	//		for (const auto& activeVoid : pLevelData->Void)
	//		{
	//			auto block = std::make_shared<dae::GameObject>();
	//			auto render = block->AddComponent<dae::RenderComponent>();
	//			auto transform = block->AddComponent<dae::TransformComponent>();

	//			block->Initialize();
	//			transform->Initialize(activeVoid.LeftTop, 0.f, block);
	//			render->Initialize(voidTexture, block);

	//			scene->Add(block);
	//		}

	//		auto texture = dae::ResourceManager::GetInstance().LoadTexture("BlueTank.png");

	//		FPS
	//		auto fpsGameobject = std::make_shared<dae::GameObject>();
	//		auto transformComp = fpsGameobject->AddComponent<dae::TransformComponent>();
	//		auto textComp = fpsGameobject->AddComponent<dae::TextObject>();
	//		auto fps = fpsGameobject->AddComponent<dae::fpsCounter>();

	//		auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);

	//		textComp->Initialize("Programming 4 Assignment", font, fpsGameobject);
	//		transformComp->Initialize(glm::vec2(500, 5), 0.f, fpsGameobject);
	//		fps->Initialize(fpsGameobject);

	//		scene->Add(fpsGameobject);
	//	}

	//	void LoadScene2(Gamemode::GameModeEnum)
	//	{
	//		auto pathWayTexture = dae::ResourceManager::GetInstance().LoadTexture("Level/Textures/path.png");
	//		auto wallTexture = dae::ResourceManager::GetInstance().LoadTexture("level/Textures/wall.png");
	//		auto voidTexture = dae::ResourceManager::GetInstance().LoadTexture("level/Textures/void.png");

	//		auto& level = dae::LevelGenerator::GetInstance();
	//		level.LoadLevel("Level/LevelLayout1.csv");

	//		static const auto scene = dae::SceneManager::GetInstance().CreateScene("2nd scene");

	//		for (const auto& pathWay : level.GetPathWay())
	//		{
	//			auto block = std::make_shared<dae::GameObject>();
	//			auto render = block->AddComponent<dae::RenderComponent>();
	//			auto transform = block->AddComponent<dae::TransformComponent>();

	//			block->Initialize();
	//			transform->Initialize(pathWay.LeftTop, 0.f, block);
	//			render->Initialize(pathWayTexture, block);


	//			scene->Add(block);
	//		}

	//		for (const auto& wall : level.GetWalls())
	//		{
	//			auto block = std::make_shared<dae::GameObject>();
	//			auto render = block->AddComponent<dae::RenderComponent>();
	//			auto transform = block->AddComponent<dae::TransformComponent>();
	//			auto collison = block->AddComponent<dae::CollisionBoxComponent>();

	//			dae::CollisionBox colBox;
	//			colBox._leftTop = wall.LeftTop;
	//			colBox._height = static_cast<float>(wall.Height);
	//			colBox._width = static_cast<float>(wall.Width);

	//			collison->Initialize(block, colBox, 0);
	//			block->Initialize();
	//			transform->Initialize(wall.LeftTop, 0.f, block);
	//			render->Initialize(wallTexture, block);

	//			scene->Add(block);
	//		}

	//		for (const auto& activeVoid : level.GetVoid())
	//		{
	//			auto block = std::make_shared<dae::GameObject>();
	//			auto render = block->AddComponent<dae::RenderComponent>();
	//			auto transform = block->AddComponent<dae::TransformComponent>();

	//			block->Initialize();
	//			transform->Initialize(activeVoid.LeftTop, 0.f, block);
	//			render->Initialize(voidTexture, block);

	//			scene->Add(block);
	//		}
	//	}

	//	void LoadScene3(Gamemode::GameModeEnum)
	//	{
	//		auto pathWayTexture = dae::ResourceManager::GetInstance().LoadTexture("Level/Textures/path.png");
	//		auto wallTexture = dae::ResourceManager::GetInstance().LoadTexture("level/Textures/wall.png");
	//		auto voidTexture = dae::ResourceManager::GetInstance().LoadTexture("level/Textures/void.png");

	//		static const auto scene = dae::SceneManager::GetInstance().CreateScene("3th scene");

	//		auto& level = dae::LevelGenerator::GetInstance();
	//		level.LoadLevel("Level/LevelLayout2.csv");

	//		for (const auto& pathWay : level.GetPathWay())
	//		{
	//			auto block = std::make_shared<dae::GameObject>();
	//			auto render = block->AddComponent<dae::RenderComponent>();
	//			auto transform = block->AddComponent<dae::TransformComponent>();

	//			block->Initialize();
	//			transform->Initialize(pathWay.LeftTop, 0.f, block);
	//			render->Initialize(pathWayTexture, block);


	//			scene->Add(block);
	//		}

	//		for (const auto& wall : level.GetWalls())
	//		{
	//			auto block = std::make_shared<dae::GameObject>();
	//			auto render = block->AddComponent<dae::RenderComponent>();
	//			auto transform = block->AddComponent<dae::TransformComponent>();
	//			auto collison = block->AddComponent<dae::CollisionBoxComponent>();

	//			dae::CollisionBox colBox;
	//			colBox._leftTop = wall.LeftTop;
	//			colBox._height = static_cast<float>(wall.Height);
	//			colBox._width = static_cast<float>(wall.Width);

	//			collison->Initialize(block, colBox, 0);
	//			block->Initialize();
	//			transform->Initialize(wall.LeftTop, 0.f, block);
	//			render->Initialize(wallTexture, block);

	//			scene->Add(block);
	//		}

	//		for (const auto& activeVoid : level.GetVoid())
	//		{
	//			auto block = std::make_shared<dae::GameObject>();
	//			auto render = block->AddComponent<dae::RenderComponent>();
	//			auto transform = block->AddComponent<dae::TransformComponent>();

	//			block->Initialize();
	//			transform->Initialize(activeVoid.LeftTop, 0.f, block);
	//			render->Initialize(voidTexture, block);

	//			scene->Add(block);
	//		}
	//	}
	//};

}
