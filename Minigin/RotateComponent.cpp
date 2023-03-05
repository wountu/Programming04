#include "RotateComponent.h"
#include "TimeClass.h"
#include "GameObject.h"

#include <iostream>

void dae::RotateComponent::Initialize(std::shared_ptr<GameObject> parent, float radius)
{
	m_radius = radius;

	m_Parent = parent;
	m_transform = m_Parent->GetComponent<TransformComponent>();
	m_position.x = radius;
	m_position.y = 0;
}

void dae::RotateComponent::Update()
{
	auto& timer = TimeClass::GetInstance();

	const float angleIncrement{ 120.f };
	m_angle += timer.GetElapsed() * angleIncrement;

	if (m_angle > 360)
		m_angle = 0.f;

	m_position.x = cos(3.14f / 180.f * m_angle) * m_radius;
	m_position.y = sin(3.14f / 180.f * m_angle) * m_radius;

	m_transform->ChangePosition(m_position);
}
