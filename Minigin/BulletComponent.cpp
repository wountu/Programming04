#include "BulletComponent.h"
#include "TimeClass.h"
#include "CollisionBoxComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "HealthComponent.h"

void dae::BulletComponent::Initialize(std::shared_ptr<GameObject> parent)
{
	m_Parent = parent.get();

	m_Transform = m_Parent->GetComponent<TransformComponent>().get();

}

void dae::BulletComponent::Update()
{
	const float speed{ 200.f };
	auto& timeClass = TimeClass::GetInstance();

	auto oldPos = m_Transform->GetLocalPosition();

	auto offset = (speed * m_Transform->GetDirection() * timeClass.GetElapsed());

	glm::vec2 newPos = oldPos + offset;

	m_Transform->ChangeLocalPosition(newPos);
	
	auto overlap = m_Parent->GetComponent<CollisionBoxComponent>()->GetOverlappingGameObject();
	if(overlap != m_OverlappedObject)
	{
		m_OverlappedObject = overlap;

		if (overlap && overlap->GetTag() != m_Parent->GetTag()) //If we have an overlap that isn't our tank
		{
			auto overlapTag = overlap->GetTag();

			if (overlapTag != dae::Static && overlapTag != m_Parent->GetTag())
			{
				m_Destroy = true;
				overlap->GetComponent<HealthComponent>()->LoseHealth();
			}

			else if (overlapTag == dae::Static)
			{
				m_Transform->SetDirection({ m_Transform->GetDirection().x * -1, m_Transform->GetDirection().y * -1 });
			}
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
