#include <iostream>
#include "TransformComponent.h"
#include "GameObject.h"

namespace dae
{
	void TransformComponent::Initialize(const glm::vec2& pos, float angle, std::shared_ptr<GameObject> parent)
	{
		m_position = pos;
		m_Angle = angle;
		//m_pParent = parent;

		m_Parent = parent.get();
	}

	void TransformComponent::Update()
	{
		m_Parent->SetLocalPos(m_position);
	}

	TransformComponent::~TransformComponent()
	{
	}

	void TransformComponent::ChangePosition(glm::vec2 pos)
	{
		m_position = pos;
	}

	glm::vec2 TransformComponent::GetPosition() const
	{
		return m_position;
	}

	void TransformComponent::ChangeAngle(float angle)
	{
		m_Angle = angle;
	}

	float TransformComponent::GetAngle() const
	{
		return m_Angle;
	}


}
