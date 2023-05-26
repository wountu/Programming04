#include "BulletComponent.h"
#include "TimeClass.h"

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
}

void dae::BulletComponent::Render() const
{
}
