#include "BulletComponent.h"
#include "TimeClass.h"
#include "CollisionBoxComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "HealthComponent.h"

void dae::BulletComponent::Initialize(std::shared_ptr<GameObject> parent, glm::vec2 direction)
{
	m_Parent = parent.get();
	m_Direction = direction;

	m_Transform = m_Parent->GetComponent<TransformComponent>().get();
}

void dae::BulletComponent::Update()
{
	const float speed{ 100.f };
	auto& timeClass = TimeClass::GetInstance();

	auto oldPos = m_Transform->GetPosition();
	auto offset = (speed * m_Direction * timeClass.GetElapsed());
	glm::vec2 newPos = oldPos + offset;


	m_Transform->ChangePosition(newPos);
	
	auto overlap = m_Parent->GetComponent<CollisionBoxComponent>()->GetOverlappingGameObject();
	if (overlap && overlap != m_Parent->GetParent()) //If we have an overlap that isn't our tank
	{
		auto overlapTag = overlap->GetTag(); 

		if (overlapTag != dae::Static)
		{
			m_Destroy = true;
			//overlap->GetComponent<HealthComponent>()->LoseHealth(1);
		}
	}
}

void dae::BulletComponent::Render() const
{
}

bool dae::BulletComponent::GetDestroy() const
{
	return m_Destroy;
}
