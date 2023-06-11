#include "SceneManager.h"
#include "SceneManager.h"
#include "Scene.h"

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
		}
	}
}

void dae::SceneManager::SetNextLevelActive()
{
	//m_ActiveScene->Deactivate();
	//m_ActiveScene = m_scenes[1];
	//m_ActiveScene->Activate();
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
