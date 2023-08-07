#include "SceneManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "GameObject.h"

#include <iostream>

void dae::SceneManager::Update()
{
	m_ActiveScene->Update();
	//for(auto& scene : m_scenes)
	//{
	//	scene->Update();
	//}
}

void dae::SceneManager::FixedUpdate(float)
{

}

void dae::SceneManager::Render()
{
	m_ActiveScene->Render();
	//for (const auto& scene : m_scenes)
	//{
	//	scene->Render();
	//}
}

void dae::SceneManager::SetActiveScene(std::shared_ptr<Scene> scene)
{
	for (const auto& loopScene : m_scenes)
	{
		if (loopScene == scene)
		{
			if (m_ActiveScene != nullptr)
				m_ActiveScene->Deactivate();

			m_ActiveScene = scene;
			m_ActiveScene->Activate();
			//std::cout << "Switch scene\n";
		}
	}
}

void dae::SceneManager::SetNextLevelActive()
{
	size_t newLevelIdx{};
	for (size_t idx{}; idx < m_scenes.size(); ++idx)
	{
		if (m_scenes[idx] == m_ActiveScene)
		{
			newLevelIdx = idx + 1;
			if (newLevelIdx == m_scenes.size())
				newLevelIdx = 0;
		}
	}

	SetActiveScene(m_scenes[newLevelIdx]);
}

void dae::SceneManager::SetSceneByIdx(int idx)
{
	SetActiveScene(m_scenes[idx]);
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetActiveScene() const
{
	return m_ActiveScene;
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetScene(int idx) const
{
	return m_scenes[idx];
}

std::shared_ptr<dae::Scene> dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::make_shared<Scene>(name);
	m_scenes.push_back(scene);
	return scene;
}

std::shared_ptr<dae::Scene> dae::SceneManager::CreateScene(const std::string& name, dae::LevelData* pLevelData)
{
	const auto scene = std::make_shared<Scene>(name);

	auto pathWayTexture = dae::ResourceManager::GetInstance().LoadTexture("Level/Textures/path.png");
	auto wallTexture = dae::ResourceManager::GetInstance().LoadTexture("level/Textures/wall.png");
	auto voidTexture = dae::ResourceManager::GetInstance().LoadTexture("level/Textures/void.png");

	//static const auto scene = dae::SceneManager::GetInstance().CreateScene("1st scene");

	//auto& level = dae::LevelGenerator::GetInstance();
	//std::unique_ptr<LevelData> pLevelData = level.LoadLevel("Level/LevelLayout0.csv");

	for (const auto& pathWay : pLevelData->pathWays)
	{
		auto block = std::make_shared<dae::GameObject>();
		auto render = block->AddComponent<dae::RenderComponent>();
		auto transform = block->AddComponent<dae::TransformComponent>();

		block->Initialize();
		transform->Initialize(pathWay.LeftTop, 0.f, block);
		render->Initialize(pathWayTexture, block);


		scene->Add(block);
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

		scene->Add(block);
	}

	for (const auto& activeVoid : pLevelData->Void)
	{
		auto block = std::make_shared<dae::GameObject>();
		auto render = block->AddComponent<dae::RenderComponent>();
		auto transform = block->AddComponent<dae::TransformComponent>();

		block->Initialize();
		transform->Initialize(activeVoid.LeftTop, 0.f, block);
		render->Initialize(voidTexture, block);

		scene->Add(block);
	}
	
	m_scenes.push_back(scene);
	return scene;
}
