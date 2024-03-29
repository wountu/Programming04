#include <iostream>
#include "TransformComponent.h"
#include "GameObject.h"
#include <glm/glm.hpp>

namespace dae
{
	void TransformComponent::Initialize(const glm::vec2& pos, float angle, std::shared_ptr<GameObject> parent, bool keepWorldPos)
	{
		m_Angle = angle;

		m_Parent = parent.get();
		m_Collision = m_Parent->GetComponent<CollisionBoxComponent>();

		m_KeepWorldPos = keepWorldPos;

		m_LocalPosition = pos;
		SetPositionDirty();
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
		CollisionUpdate();
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

		if (std::abs(m_Direction.x) != 1)
			m_Direction.x = 0;

		if (std::abs(m_Direction.y) != 1)
			m_Direction.y = 0;
	}

	float TransformComponent::GetAngle() const
	{
		return m_Angle;
	}


	glm::vec2 TransformComponent::GetDirection() const
	{
		return m_Direction;
	}

	void TransformComponent::SetDirection(glm::vec2 direction)
	{
		m_Direction = direction;

		m_Angle = static_cast<float>(atan2(m_Direction.y, m_Direction.x));
		m_Angle = glm::degrees(m_Angle);
	}

	void TransformComponent::SetPositionDirty()
	{
		auto children = m_Parent->GetChildren();
		for (const auto& child : children)
		{
			auto trans = child->GetComponent<TransformComponent>();
			if (trans && !trans->GetKeepWorldPos())
			{
				trans->SetPositionDirty();
			}
		}

		m_DirtyFlag = true;
	}

	bool TransformComponent::GetKeepWorldPos() const
	{
		return m_KeepWorldPos;
	}

	void TransformComponent::CollisionUpdate()
	{
		if (m_Collision)
		{
			auto collisionBox = m_Collision->GetOverlappingGameObject();
			const int replaceOffsetWidth{ 2 }; //The distance to set the collision from the other collision

			if (collisionBox && collisionBox->GetTag() != dae::Bullet)
			{
				auto otherBox = collisionBox->GetComponent<CollisionBoxComponent>()->GetBox();
   				auto parentBox = m_Parent->GetComponent<CollisionBoxComponent>()->GetBox();

				//Left collision
				if (m_Direction.x == -1 && otherBox._leftTop.x < parentBox._leftTop.x) //if we go to the left and enter the other box on the right
				{
					float leftOverlapWidth = (otherBox._leftTop.x + otherBox._width) - parentBox._leftTop.x; //The amount it has crossed on the left
					if (leftOverlapWidth > 0)
					{
						m_LocalPosition.x += leftOverlapWidth + replaceOffsetWidth; //Put it back out of the collision
					}
				}

				//Right collision
				if (m_Direction.x == 1 && otherBox._leftTop.x > parentBox._leftTop.x) //If we go to the right and enter the other box on the left
				{
					float rightOverlapWidth = (parentBox._leftTop.x + parentBox._width) - otherBox._leftTop.x; //The amount it has crossed on the right
					if (rightOverlapWidth > 0)
					{
						m_LocalPosition.x -= rightOverlapWidth + replaceOffsetWidth; //Put it back out of the collision
					}
				}

				//Top collision
				if (m_Direction.y == -1 && otherBox._leftTop.y < parentBox._leftTop.y) //If we go up and enter the box on the bottom
				{
					float topOverlapWidth = parentBox._leftTop.y - (otherBox._leftTop.y + otherBox._height);
					if (topOverlapWidth < 0)
					{
						m_LocalPosition.y -= topOverlapWidth + replaceOffsetWidth; //Put it back out of collision
					}
				}

				//Bottom collision
				if (m_Direction.y == 1 && otherBox._leftTop.y > parentBox._leftTop.y) //If we go down and enter the box on the top
				{
					float botOverlapWidth = otherBox._leftTop.y - (parentBox._leftTop.y + parentBox._height);
					if (botOverlapWidth < 0)
					{
						m_LocalPosition.y += botOverlapWidth + replaceOffsetWidth; //Put it back out of collision
					}
				}
			}
		}
	}

	void TransformComponent::UpdateWorldPos()
	{
		if (m_DirtyFlag)
		{
			if (m_Parent->GetParent() == nullptr || m_KeepWorldPos)
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
