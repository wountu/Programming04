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

	dae::ServiceLocator::GetSoundSystem().LoadSound(1, "Shoot.wav");


	m_Texture = dae::ResourceManager::GetInstance().LoadTexture("BulletPlayer.png");
}

void dae::BulletManager::Update()
{
	//Remove the bullet from the scene 

	std::shared_ptr<GameObject> bulletToDelete { nullptr };

	for (auto& bullet : m_pBullets)
	{
		if (bullet->GetComponent<BulletComponent>()->GetDestroy())
		{
			bullet->GetParent()->RemoveChild(bullet);
			bulletToDelete = bullet;
			SceneManager::GetInstance().GetScene(0)->Remove(bullet);
		}
	}

	if (bulletToDelete)
		m_pBullets.erase(std::remove(m_pBullets.begin(), m_pBullets.end(), bulletToDelete), m_pBullets.end());

}

void dae::BulletManager::Render() const
{
}

void dae::BulletManager::SpawnBullet(glm::vec2, glm::vec2)
{
	//Sound system
	auto& system = dae::ServiceLocator::GetSoundSystem();
	system.Play(1, 50);

	//GameObject
	std::shared_ptr<GameObject> bullet = std::make_unique<GameObject>();
	bullet->SetParent(m_Parent->shared_from_this(), false);
	
	//Transform
	auto transform = bullet->AddComponent<TransformComponent>();
	const auto parentTransform = m_Parent->GetComponent<TransformComponent>();
	transform->Initialize(parentTransform->GetLocalPosition(), parentTransform->GetAngle(), bullet);

	//Render
	auto render = bullet->AddComponent<RenderComponent>();
	render->Initialize(m_Texture, bullet);

	//Bullet
	auto bulletComp = bullet->AddComponent<BulletComponent>();
	bulletComp->Initialize(bullet, parentTransform->GetDir());

	//Collision
	auto collision = bullet->AddComponent<CollisionBoxComponent>();
	CollisionBox box;
	box._height = static_cast<float>(m_Texture->GetSize().y);
	box._width = static_cast<float>(m_Texture->GetSize().x);
	box._leftTop = transform->GetLocalPosition();
	collision->Initialize(bullet, box);

	//Store bullet
	m_pBullets.emplace_back(bullet);

	std::cout << "Spawn in bullet" << "\n";
}
