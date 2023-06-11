#include "VisionComponent.h"
#include "GameObject.h"
#include "Renderer.h"

#include <SDL.h>

namespace dae
{
	void VisionComponent::Initialize(std::shared_ptr<GameObject> parent, float visionLength, glm::vec2 offset)
	{
		m_Parent = parent.get();
		m_Transform = m_Parent->GetComponent<TransformComponent>();
		m_VisionLength = visionLength;
		m_Offset = offset;
	}

	void VisionComponent::Update()
	{
		m_Direction = m_Transform->GetDirection();
		m_StartVision = m_Transform->GetWorldPosition();

		m_StartVision += m_Offset;
		
		glm::vec2 visionVec = m_Direction * m_VisionLength;
		m_EndVision = m_StartVision + visionVec;
	}

	void VisionComponent::Render() const
	{
	}

	glm::vec2 VisionComponent::GetStartVision() const
	{
		return m_StartVision;
	}

	glm::vec2 VisionComponent::GetEndVision() const
	{
		return m_EndVision;
	}

	glm::vec2 VisionComponent::GetDirection() const
	{
		return m_Direction;
	}
}