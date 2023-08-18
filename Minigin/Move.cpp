#include "Move.h"
#include "TransformComponent.h"
#include "VisionComponent.h"
#include "TimeClass.h"
#include "CollisionDetector.h"
#include "Turn.h"
#include "Shoot.h"
#include "SceneManager.h"
#include "Scene.h"
#include "RenderComponent.h"

namespace dae
{

	void Move::Initialize(AIComponent* ai, float speed)
	{
		m_AI = ai;
		m_Transform = m_AI->GetParent()->GetComponent<TransformComponent>();
		m_Speed = speed;

		m_GridWidth = GridGenerator::GetInstance().GetGridWidth();
		m_GridHeight = GridGenerator::GetInstance().GetGridHeight();

	}

	void Move::OnEnter()
	{
	}

	State* Move::Update()
	{
		//Update grid
		m_Grid = GridGenerator::GetInstance().GetGrid()[SceneManager::GetInstance().GetActiveScene()->GetLevelName()];

		if (m_Dir.x == 0 && m_Dir.y == 0)
			LookForNewDir();

		if (m_NewDir != m_Dir && CheckForTurn()) //Needs to turn when arrived at the middle of the tile
		{
			m_Dir = m_NewDir;
		}

		CheckCollision();

		glm::vec2 newPos{ m_Transform->GetWorldPosition() + m_Dir * m_Speed * TimeClass::GetInstance().GetElapsed() };
		m_Transform->ChangeLocalPosition(newPos);

		//auto collidingBoxes = CollisionDetector::GetInstance().BoxesCollidingWithRay(m_Vision->GetStartVision(), m_Vision->GetEndVision(), m_Vision->GetDirection());
		//float distSqrd{ FLT_MAX };
		//CollisionBoxComponent* closestBox{};
		////std::cout << collidingBoxes.size() << "\n";
		//
		//for(const auto& box : collidingBoxes)
		//{
		//	if (box->GetParent()->GetTag() == dae::Bullet)
		//		continue;

		//	glm::vec2 boxToRay{ m_Vision->GetStartVision() - box->GetBox()._leftTop };
		//	float newDistSqrd = (boxToRay.x * boxToRay.x) + (boxToRay.y * boxToRay.y);
		//	if (newDistSqrd < distSqrd)
		//	{
		//		closestBox = box;
		//		distSqrd = newDistSqrd;
		//	}
		//}

		//if (!closestBox)
		//	return nullptr;

		//if (closestBox->GetParent()->GetTag() != dae::AI && closestBox->GetParent()->GetTag() != dae::Static && m_AI->GetCanShoot()) //Found a possible target to shoot 
		//{
		//	m_AI->SetTargetDir(closestBox->GetParent()->GetComponent<TransformComponent>()->GetWorldPosition() - m_Transform->GetWorldPosition());
		//	auto shoot = new ShootAI();
		//	shoot->Initialize(m_AI);
		//	return shoot;
		//	//std::cout << "Target in sight // ";
		//}

		////std::cout << distSqrd << "\n";

		//if (distSqrd < 450)
		//{
		//	//std::cout << "turn" << "\n";
		//	auto turn = new Turn();
		//	turn->Initialize(m_AI, m_AI->GetTransform());
		//	return turn;
		//}

		return nullptr;
	}

	void Move::OnExit()
	{
	}

	bool Move::CanGoLeft(int idx)
	{
		int leftIdx{};

		if (idx - 1 >= 0)
		{
			leftIdx = idx - 1;

			if (m_Grid[leftIdx].walkable)
				return true;
		}

		return false;
	}

	bool Move::CanGoRight(int idx)
	{
		int rightIdx{};
		if ((idx + 1) % m_GridHeight <= m_GridWidth && idx + 1 > 0)
		{
			rightIdx = idx + 1;

			if (m_Grid[rightIdx].walkable)
				return true;

		}

		return false;
	}

	bool Move::CanGoUp(int idx)
	{
		int upIdx{};
		if (idx - m_GridWidth >= 0)
		{
			upIdx = idx - m_GridWidth;

			if (m_Grid[upIdx].walkable)
				return true;

		}

		return false;
	}

	bool Move::CanGoDown(int idx)
	{
		int downIdx{};
		if (idx + m_GridWidth <= m_GridWidth * m_GridHeight && idx + m_GridWidth > 0)
		{
			downIdx = idx + m_GridWidth;

			if (m_Grid[downIdx].walkable)
				return true;
		}

		return false;
	}

	void Move::CheckCollision()
	{
		auto& gridGen = GridGenerator::GetInstance();
		int idx = gridGen.GetIdxFromPos(m_Transform->GetWorldPosition());

		auto grid = gridGen.GetGrid()[SceneManager::GetInstance().GetActiveScene()->GetLevelName()];

		if (m_Dir.x == 1 && !CanGoRight(idx))
		{
			LookForNewDir();
		}

		if (m_Dir.x == -1 && !CanGoLeft(idx))
		{
			LookForNewDir();
		}

		if (m_Dir.y == -1 && !CanGoUp(idx))
		{
			LookForNewDir();
		}

		if (m_Dir.y == 1 && !CanGoDown(idx))
		{
			LookForNewDir();
		}
	}

	void Move::LookForNewDir()
	{
		auto& gridGen = GridGenerator::GetInstance();
		int idx = gridGen.GetIdxFromPos(m_Transform->GetWorldPosition());

		if (CanGoRight(idx))
		{
			m_NewDir.x = 1;
			m_NewDir.y = 0;
			return;
		}

		if (CanGoUp(idx))
		{
			m_NewDir.y = -1;
			m_NewDir.x = 0;
			return;
		}

		if (CanGoLeft(idx))
		{
			m_NewDir.x = -1;
			m_NewDir.y = 0;
			return;
		}

		if (CanGoDown(idx))
		{
			m_NewDir.y = 1;
			m_NewDir.x = 0;
		}
	}

	bool Move::CheckForTurn()
	{
		const int turnRadius{ 1 }; //The radius the player can be from the turning point to turn in
		auto texture = m_AI->GetParent()->GetComponent<dae::RenderComponent>()->GetTexture();

		auto pos = m_Transform->GetWorldPosition(); //Players pos

		//Find the right tile
		int idx = GridGenerator::GetInstance().GetIdxFromPos(pos);
		dae::Tile node = m_Grid[idx];

		float dist = glm::distance(pos, node.LeftTop);

		if (dist < turnRadius)
		{
			std::cout << "Turn\n";
			return true;
		}

		return false;
	}
}
