#include "Move.h"
#include "TransformComponent.h"
#include "VisionComponent.h"
#include "TimeClass.h"
#include "CollisionDetector.h"
#include "Turn.h"
#include "Shoot.h"

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
	}

	PlayerState* Move::HandleInput()
	{
		m_Transform->ChangeLocalPosition(m_Transform->GetWorldPosition() + (m_Transform->GetDirection() * m_Speed * TimeClass::GetInstance().GetElapsed()));

		auto collidingBoxes = CollisionDetector::GetInstance().BoxesCollidingWithRay(m_Vision->GetStartVision(), m_Vision->GetEndVision(), m_Vision->GetDirection());
		float distSqrd{ FLT_MAX };
		CollisionBoxComponent* closestBox{};
		//std::cout << collidingBoxes.size() << "\n";
		
		for(const auto& box : collidingBoxes)
		{
			if (box->GetParent()->GetTag() == dae::Bullet)
				continue;

			glm::vec2 boxToRay{ m_Vision->GetStartVision() - box->GetBox()._leftTop };
			float newDistSqrd = (boxToRay.x * boxToRay.x) + (boxToRay.y * boxToRay.y);
			if (newDistSqrd < distSqrd)
			{
				closestBox = box;
				distSqrd = newDistSqrd;
			}
		}

		if (!closestBox)
			return nullptr;

		if (closestBox->GetParent()->GetTag() != dae::AI && closestBox->GetParent()->GetTag() != dae::Static && m_AI->GetCanShoot()) //Found a possible target to shoot 
		{
			m_AI->SetTargetDir(closestBox->GetParent()->GetComponent<TransformComponent>()->GetWorldPosition() - m_Transform->GetWorldPosition());
			auto shoot = new ShootAI();
			shoot->Initialize(m_AI);
			return shoot;
			//std::cout << "Target in sight // ";
		}

		//std::cout << distSqrd << "\n";

		if (distSqrd < 500)
		{
			//std::cout << "turn" << "\n";
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
