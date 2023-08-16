#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene final
	{
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Add(std::vector<std::shared_ptr<GameObject>> objects);
		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();

		void Update();
		void Render() const;

		int GetCollectiblesLeft();

		Scene(const std::string& name);
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void Activate();
		void Deactivate();

		std::string GetLevelName() const;

	private: 
		std::string m_name;
		std::vector < std::shared_ptr<GameObject>> m_objects{};

		std::vector<std::shared_ptr<GameObject>> m_Collectibles{};

		static unsigned int m_idCounter; 
		bool m_Active{ false };
	};

}
