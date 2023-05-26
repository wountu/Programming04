#include "BulletManager.h"
#include "ServiceLocator.h"
#include "BulletComponent.h"

#include "RenderComponent.h"
#include "ResourceManager.h"

#include "SceneManager.h"
#include "Scene.h"

void dae::BulletManager::Initialize(std::shared_ptr<GameObject> parent)
{
	m_Parent = parent.get();

	dae::ServiceLocator::GetSoundSystem().LoadSound(1, "TankShot.wav");


	m_Texture = dae::ResourceManager::GetInstance().LoadTexture("BulletPlayer.png");
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

	std::shared_ptr<GameObject> bullet = std::make_unique<GameObject>();
	bullet->SetParent(m_Parent->shared_from_this(), false);
	
	auto transform = bullet->AddComponent<TransformComponent>();
	glm::vec2 pos = m_Parent->GetComponent<TransformComponent>()->GetPosition();
	pos.x += 30.f;
	transform->Initialize(pos, 0.f, bullet);

	auto render = bullet->AddComponent<RenderComponent>();
	render->Initialize(m_Texture, bullet);

	auto bulletComp = bullet->AddComponent<BulletComponent>();
	bulletComp->Initialize(bullet, glm::vec2(1, 0));

	SceneManager::GetInstance().GetScene(0)->Add(bullet);

	system.Play(1, 50);

	std::cout << "Spawn in bullet" << "\n";
}
