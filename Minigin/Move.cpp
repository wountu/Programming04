#include "Move.h"
#include "TransformComponent.h"
#include "VisionComponent.h"

namespace dae
{

	Move::Move(std::shared_ptr<TransformComponent> transform, std::shared_ptr<VisionComponent> vision, float speed)
		:m_Transform{ transform },
		m_Vision{ vision },
		m_Speed{ speed }
	{
	}

	void Move::OnEnter()
	{
		m_Transform->SetDirection(glm::vec2(1, 0));
	}

	PlayerState* Move::HandleInput()
	{
		m_Transform->ChangeLocalPosition(m_Transform->GetLocalPosition() + (m_Transform->GetDirection() * m_Speed));

		return nullptr;
	}

	void Move::OnExit()
	{
	}
}
