#include "Move.h"
#include "TransformComponent.h"
#include "VisionComponent.h"
#include "TimeClass.h"
#include "CollisionDetector.h"
#include "Turn.h"

namespace dae
{

	void Move::Initialize(AIComponent* ai, std::shared_ptr<TransformComponent> transform, std::shared_ptr<VisionComponent> vision, float speed)
	{
		m_AI = ai;
		m_Transform = transform;
		m_Vision = vision;
		m_Speed = speed;
	}

	void Move::OnEnter()
	{
		//m_Transform->SetDirection(glm::vec2(-1, 0));
	}

	PlayerState* Move::HandleInput()
	{
		m_Transform->ChangeLocalPosition(m_Transform->GetLocalPosition() + (m_Transform->GetDirection() * m_Speed * TimeClass::GetInstance().GetElapsed()));

		auto collidingBox = CollisionDetector::GetInstance().BoxCollidingWithRay(m_Vision->GetStartVision(), m_Vision->GetEndVision(), m_Vision->GetDirection());
		
		if (collidingBox)
		{
			glm::vec2 boxToRay{ m_Transform->GetLocalPosition() - collidingBox->GetBox()._leftTop };
			float distSqrd = boxToRay.x * boxToRay.x + boxToRay.y + boxToRay.y;
			if (distSqrd < 50)
			{
				std::cout << "turn" << "\n";
				auto turn = new Turn();
				turn->Initialize(m_AI, m_AI->GetTransform());
				return turn;
			}
		}

		return nullptr;
	}

	void Move::OnExit()
	{
	}
}
