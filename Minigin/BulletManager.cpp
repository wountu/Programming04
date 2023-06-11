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
			bullet->RemoveAllComponents();
			bulletToDelete = bullet;
		}
	}

	if (bulletToDelete)
		m_pBullets.erase(std::remove(m_pBullets.begin(), m_pBullets.end(), bulletToDelete), m_pBullets.end());

}

void dae::BulletManager::Render() const
{
}

void dae::BulletManager::SpawnBullet(glm::vec2 dir)
{
	//Sound system
	auto& system = dae::ServiceLocator::GetSoundSystem();
	system.Play(1, 50);

	const float textureWidth = static_cast<float>(m_Texture->GetSize().x);

	//GameObject
	std::shared_ptr<GameObject> bullet = std::make_unique<GameObject>();
	
	//Transform
	auto transform = bullet->AddComponent<TransformComponent>();
	const auto parentTransform = m_Parent->GetComponent<TransformComponent>();
	
	//Allignment with gun
	auto tankCol = m_Parent->GetParent()->GetComponent<CollisionBoxComponent>();
	glm::vec2 allignedWithGun{ parentTransform->GetLocalPosition().x + tankCol->GetBox()._width, parentTransform->GetLocalPosition().y + tankCol->GetBox()._height / 2 };

	auto bulletPos = parentTransform->GetWorldPosition() + allignedWithGun;

	transform->Initialize(bulletPos, parentTransform->GetAngle(), bullet, true);
	transform->SetDirection(dir);

	//Render
	auto render = bullet->AddComponent<RenderComponent>();
	render->Initialize(m_Texture, bullet);

	//Bullet
	auto bulletComp = bullet->AddComponent<BulletComponent>();
	bulletComp->Initialize(bullet);

	//Collision
	auto collision = bullet->AddComponent<CollisionBoxComponent>();
	CollisionBox box;
	box._height = static_cast<float>(m_Texture->GetSize().y);
	box._width = textureWidth;
	box._leftTop = transform->GetWorldPosition();
	collision->Initialize(bullet, box, 0);

	//Initialize the gameobject
	bullet->Initialize();
	bullet->SetTag(dae::Bullet);
	bullet->SetParent(m_Parent->shared_from_this(), false);

	//Store bullet
	m_pBullets.emplace_back(bullet);

	SceneManager::GetInstance().GetScene(0)->Add(bullet);

	std::cout << "Spawn in bullet" << "\n";
}
