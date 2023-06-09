#include <iostream>
#include "TransformComponent.h"
#include "GameObject.h"

namespace dae
{
	void TransformComponent::Initialize(const glm::vec2& pos, float angle, std::shared_ptr<GameObject> parent)
	{
		m_Angle = angle;
		//m_pParent = parent;

		m_Parent = parent.get();
		m_Collision = m_Parent->GetComponent<CollisionBoxComponent>();

		m_LocalPosition = pos;
		SetPositionDirty();
	}

	void TransformComponent::Update()
	{
		m_Parent->SetLocalPos(m_WorldPosition);

		//if (m_Parent->GetTag() == Tag::Player1)
		//{
		//	std::cout << m_LocalPosition.x << ", " << m_LocalPosition.y << "\n";
		//}
	}

	TransformComponent::~TransformComponent()
	{
	}

	void TransformComponent::ChangeLocalPosition(glm::vec2 pos)
	{
		m_LocalPosition = pos;
		SetPositionDirty();
		CollisionUpdate();
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

	void TransformComponent::CollisionUpdate()
	{
		if (m_Collision)
		{
			auto collisionBox = m_Collision->GetOverlappingGameObject();

			if (collisionBox)
			{
				std::cout << "Overlapping" << "\n";
			}
		}
	}

	void TransformComponent::UpdateWorldPos()
	{
		if (m_DirtyFlag)
		{
			if (m_Parent->GetParent() == nullptr)
				m_WorldPosition = m_LocalPosition;

			else
			{
				auto transform = m_Parent->GetParent()->GetComponent<TransformComponent>();
				m_WorldPosition = transform->GetWorldPosition() + m_LocalPosition;
			}
		}

		m_DirtyFlag = false;
	}
}
