#include <iostream>
#include "TransformComponent.h"
#include "GameObject.h"

namespace dae
{
	void TransformComponent::Initialize(const glm::vec2& pos, float angle, std::shared_ptr<GameObject> parent)
	{
		m_WorldPosition = pos;
		m_Angle = angle;
		//m_pParent = parent;

		m_Parent = parent.get();
	}

	void TransformComponent::Update()
	{
		m_Parent->SetLocalPos(m_WorldPosition);
	}

	TransformComponent::~TransformComponent()
	{
	}

	void TransformComponent::ChangeLocalPosition(glm::vec2 pos)
	{
		m_LocalPosition = pos;
		SetPositionDirty();
	}

	glm::vec2 TransformComponent::GetLocalPosition() const
	{	
		return m_LocalPosition;
	}

	glm::vec2 TransformComponent::GetWorldPosition()
	{
		if (m_DirtyFlag)
			UpdateWorldPos();

		return m_WorldPosition;
	}

	void TransformComponent::ChangeAngle(float angle)
	{
		m_Angle = angle;


		m_Direction.x = cos(glm::radians(m_Angle));
		m_Direction.y = sin(glm::radians(m_Angle));
	}

	float TransformComponent::GetAngle() const
	{
		return m_Angle;
	}

	glm::vec2 TransformComponent::GetDir() const
	{
		return m_Direction;
	}

	void TransformComponent::SetPositionDirty()
	{
		auto children = m_Parent->GetChildren();
		for (const auto& child : children)
		{
			auto trans = child->GetComponent<TransformComponent>();
			trans->SetPositionDirty();
		}

		m_DirtyFlag = true;
	}

	void TransformComponent::UpdateWorldPos()
	{
		if (!m_Parent->GetParent())
			m_WorldPosition = m_LocalPosition;

		else
		{
			auto transform = m_Parent->GetComponent<TransformComponent>();
			m_WorldPosition = transform->GetWorldPosition() + m_LocalPosition;
		}

		m_DirtyFlag = false;
	}
}
