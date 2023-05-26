#include "BulletManager.h"
#include "ServiceLocator.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"

#include "BulletComponent.h"
#include "RenderComponent.h"
#include "CollisionBoxComponent.h"

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
	const auto parentTransform = m_Parent->GetComponent<TransformComponent>();
	transform->Initialize(parentTransform->GetPosition(), parentTransform->GetAngle(), bullet);

	auto render = bullet->AddComponent<RenderComponent>();
	render->Initialize(m_Texture, bullet);

	auto bulletComp = bullet->AddComponent<BulletComponent>();
	bulletComp->Initialize(bullet, parentTransform->GetDir());

	auto collision = bullet->AddComponent<CollisionBoxComponent>();
	CollisionBox box;
	box._height = static_cast<float>(m_Texture->GetSize().y);
	box._width = static_cast<float>(m_Texture->GetSize().x);
	box._leftTop = transform->GetPosition();
	collision->Initialize(bullet, box);

	SceneManager::GetInstance().GetScene(0)->Add(bullet);

	system.Play(1, 50);

	std::cout << "Spawn in bullet" << "\n";
}
