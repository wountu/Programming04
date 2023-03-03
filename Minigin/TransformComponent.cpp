#include <iostream>
#include "TransformComponent.h"

namespace dae
{
	void TransformComponent::Initialize(const glm::vec2& pos, std::shared_ptr<GameObject> parent)
	{
		m_position = pos;
		m_Parent = parent;
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


}
