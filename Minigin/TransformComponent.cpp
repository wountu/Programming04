#include <iostream>
#include "TransformComponent.h"

namespace dae
{
	void TransformComponent::Initialize(const glm::vec2& pos)
	{
		std::cout << "Init << " << pos.x << ", " << pos.y << "\n";
		m_position = pos;
	}

	void TransformComponent::SetOwner(std::weak_ptr<GameObject> parent)
	{
		m_Parent = parent;
	}

	TransformComponent::~TransformComponent()
	{
	}

	void TransformComponent::ChangePosition(glm::vec2 pos)
	{
		std::cout << "Change << " << pos.x << ", " << pos.y << "\n";
		m_position = pos;
	}

	glm::vec2 TransformComponent::GetPosition() const
	{
		return m_position;
	}


}
