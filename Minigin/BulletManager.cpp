#include "BulletManager.h"
#include "ServiceLocator.h"
#include "BulletComponent.h"

void dae::BulletManager::Initialize(std::shared_ptr<GameObject> parent)
{
	m_Parent = parent.get();

	dae::ServiceLocator::GetSoundSystem().LoadSound(1, "TankShot.wav");
}

void dae::BulletManager::Update()
{
}

void dae::BulletManager::Render() const
{
}

void dae::BulletManager::SpawnBullet(glm::vec2, glm::vec2)
{
	auto& system = dae::ServiceLocator::GetSoundSystem();

	//dae::sound_id sound = 1;
	//system.LoadSound(sound, "TankShot.wav");

	std::unique_ptr<BulletComponent> bullet = std::make_unique<BulletComponent>();
	
	system.Play(1, 50);

	std::cout << "Spawn in bullet" << "\n";
}
