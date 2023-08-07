#include "PlayerComponent.h"
#include "GameObject.h"
#include "TimeClass.h"

dae::PlayerComponent::~PlayerComponent()
{
}

void dae::PlayerComponent::Initialize(std::shared_ptr<GameObject> parent, const float movementSpeed)
{
	m_Transform = parent->GetComponent<TransformComponent>();
	m_MovementSpeed = movementSpeed;
}

void dae::PlayerComponent::Update()
{
	m_Transform->ChangeLocalPosition(m_Transform->GetWorldPosition() +
		(m_Direction * m_MovementSpeed * TimeClass::GetInstance().GetElapsed()));
}

void dae::PlayerComponent::SetDirection(glm::vec2 dir)
{
	m_Direction = dir;
}
