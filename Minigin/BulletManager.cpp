#include "BulletManager.h"

void dae::BulletManager::Initialize(std::shared_ptr<GameObject> parent)
{
	m_Parent = parent.get();
}

void dae::BulletManager::Update()
{
}

void dae::BulletManager::Render() const
{
}

void dae::BulletManager::SpawnBullet(glm::vec2, glm::vec2)
{
	std::cout << "Spawn in bullet" << "\n";
}
