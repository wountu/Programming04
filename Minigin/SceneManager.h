#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		std::shared_ptr<Scene> CreateScene(const std::string& name);

		void Update();
		void FixedUpdate(float timeStep);
		void Render();

		void SetActiveScene(std::shared_ptr<Scene> scene);

		std::shared_ptr<Scene> GetScene(int idx) const;
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;

		std::shared_ptr<Scene> m_ActiveScene{};
	};
}
