#include <iostream>
#include "TransformComponent.h"
#include "GameObject.h"

namespace dae
{
	void TransformComponent::Initialize(const glm::vec2& pos, std::shared_ptr<GameObject> parent)
	{
		m_position = pos;
		m_pParent = parent.get();
	}

	TransformComponent::~TransformComponent()
	{
		delete m_pParent;
		m_pParent = nullptr;
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
