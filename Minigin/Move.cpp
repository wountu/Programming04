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

		auto collidingBoxes = CollisionDetector::GetInstance().BoxesCollidingWithRay(m_Vision->GetStartVision(), m_Vision->GetEndVision(), m_Vision->GetDirection());
		float distSqrd{ FLT_MAX };

		std::cout << collidingBoxes.size() << "\n";
		
		for(const auto& box : collidingBoxes)
		{
			glm::vec2 boxToRay{ m_Transform->GetLocalPosition() - box->GetBox()._leftTop };
			float newDistSqrd = (boxToRay.x * boxToRay.x) + (boxToRay.y + boxToRay.y);
			if (abs(newDistSqrd) < abs(distSqrd))
			{
				distSqrd = newDistSqrd;
			}
		}

		//std::cout << distSqrd << "\n";

		if (abs(distSqrd) < 500)
		{
			std::cout << "turn" << "\n";
			auto turn = new Turn();
			turn->Initialize(m_AI, m_AI->GetTransform());
			return turn;
		}

		return nullptr;
	}

	void Move::OnExit()
	{
	}
}
