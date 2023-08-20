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
#include "Chase.h"

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
			m_LastDir = m_Dir; //To not keep going left-right-left
			m_Dir = m_NewDir;
			if (m_Dir.x != 0)
				m_MovingAlongX = true;
			if (m_Dir.y != 0)
				m_MovingAlongX = false;
		}

		//Check for new turns
		CheckCollision();
		LookForNewDir();

		//Update pos
		glm::vec2 newPos{ m_Transform->GetWorldPosition() + m_Dir * m_Speed * TimeClass::GetInstance().GetElapsed() };
		m_Transform->ChangeLocalPosition(newPos);

		//Update the grid info
		int idx = GridGenerator::GetInstance().GetIdxFromPos(m_Transform->GetWorldPosition());
		if (idx != m_CurrentTileIdx)
		{
			m_LastTileIdx = m_CurrentTileIdx;
			m_CurrentTileIdx = idx;
			m_LastTiles.push_back(idx);
			if (m_LastTiles.size() >= m_NmbrOfTilesToKeep)
			{
				m_LastTiles.pop_front();
			}
		}



		//auto objects = m_Vision->ClosestSeenObjects();
		//for (const auto& object : objects)
		//{
		//	if (object->GetTag() == dae::Player1 || object->GetTag() == dae::Player2)
		//	{
		//		std::cout << "Chase\n";
		//		//auto chase = new Chase{};
		//		//chase->Initialize(m_AI);
		//		//return chase;
		//	}
		//}

		return nullptr;
	}

	void Move::OnExit()
	{
	}

	bool Move::CanGoLeft(int idx)
	{
		int leftIdx{ idx - 1 };

		if (leftIdx >= 0 && m_LastTileIdx != leftIdx)
		{
			if (m_Grid[leftIdx].walkable)
				return true;
		}

		return false;
	}

	bool Move::CanGoRight(int idx)
	{
		size_t rightIdx{ static_cast<size_t>(idx + 1) };
		if (static_cast<int>(rightIdx) % m_GridHeight <= m_GridWidth && idx + 1 > 0 && m_LastTileIdx != static_cast<int>(rightIdx) && rightIdx < m_Grid.size())
		{
			if (m_Grid[rightIdx].walkable)
				return true;

		}

		return false;
	}

	bool Move::CanGoUp(int idx)
	{
		int upIdx{ idx - m_GridWidth };
		if (upIdx >= 0 && m_LastTileIdx != upIdx)
		{
			if (m_Grid[upIdx].walkable)
				return true;
		}

		return false;
	}

	bool Move::CanGoDown(int idx)
	{
		size_t downIdx{ static_cast<size_t>(idx + m_GridWidth) };
		if (static_cast<int>(downIdx) <= m_GridWidth * m_GridHeight && idx + m_GridWidth > 0 && m_LastTileIdx != static_cast<int>(downIdx) && downIdx < m_Grid.size())
		{
			if (m_Grid[downIdx].walkable)
				return true;
		}

		return false;
	}

	void Move::CheckCollision()
	{
		auto& gridGen = GridGenerator::GetInstance();
		//int idx = gridGen.GetIdxFromPos(m_Transform->GetWorldPosition());

		auto grid = gridGen.GetGrid()[SceneManager::GetInstance().GetActiveScene()->GetLevelName()];

		if (m_Dir.x == 1 && !CanGoRight(m_CurrentTileIdx))
		{
			LookForNewDir();
		}

		if (m_Dir.x == -1 && !CanGoLeft(m_CurrentTileIdx))
		{
			LookForNewDir();
		}

		if (m_Dir.y == -1 && !CanGoUp(m_CurrentTileIdx))
		{
			LookForNewDir();
		}

		if (m_Dir.y == 1 && !CanGoDown(m_CurrentTileIdx))
		{
			LookForNewDir();
		}
	}

	void Move::LookForNewDir()
	{
		auto& gridGen = GridGenerator::GetInstance();
		int idx = gridGen.GetIdxFromPos(m_Transform->GetWorldPosition());

		int possibiltys{};
		bool canGoUp{};
		bool canGoDown{};
		bool canGoRight{};
		bool canGoLeft{};

		if (CanGoUp(idx))
		{
			++possibiltys;
			canGoUp = true;
			m_NewDir.y = -1;
			m_NewDir.x = 0;
		}

		if (CanGoRight(idx))
		{
			++possibiltys;
			canGoRight = true;
			m_NewDir.x = 1;
			m_NewDir.y = 0;
		}

		if (CanGoLeft(idx))
		{
			++possibiltys;
			canGoLeft = true;
			m_NewDir.x = -1;
			m_NewDir.y = 0;
		}

		if (CanGoDown(idx))
		{
			++possibiltys;
			canGoDown = true;
			m_NewDir.y = 1;
			m_NewDir.x = 0;
		}

		CheckIfUpcomingTyleVisitedRecently(canGoLeft, canGoRight, canGoUp, canGoDown);
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

	void Move::CheckIfUpcomingTyleVisitedRecently(bool canGoLeft, bool canGoRight, bool canGoUp, bool canGoDown)
	{
		if (canGoRight)
		{
			int rightIdx{ (m_CurrentTileIdx + 1) };
			if (std::find(m_LastTiles.begin(), m_LastTiles.end(), rightIdx) != m_LastTiles.end() && (canGoLeft || canGoUp || canGoDown))
			{
				m_NewDir.x = 0;
			}
			else
			{
				m_NewDir.x = 1;
				m_NewDir.y = 0;

				return;
			}
		}

		if (canGoUp)
		{
			int upIdx{ m_CurrentTileIdx - m_GridWidth };
			if (std::find(m_LastTiles.begin(), m_LastTiles.end(), upIdx) != m_LastTiles.end() && (canGoLeft || canGoDown))
			{
				m_NewDir.y = 0;
			}
			else
			{
				m_NewDir.y = -1;
				m_NewDir.x = 0;
				return;
			}
		}

		if (canGoDown)
		{
			int downIdx{ m_CurrentTileIdx + m_GridWidth };
			if (std::find(m_LastTiles.begin(), m_LastTiles.end(), downIdx) != m_LastTiles.end() && canGoLeft)
			{
				m_NewDir.y = 0;
			}
			else
			{
				m_NewDir.y = 1;
				m_NewDir.x = 0;

				return;
			}
		}

		if (canGoLeft)
		{
			int leftIdx{ m_CurrentTileIdx - 1 };
			if (std::find(m_LastTiles.begin(), m_LastTiles.end(), leftIdx) != m_LastTiles.end())
			{
				m_NewDir.x = 0;
			}
			else
			{
				m_NewDir.x = -1;
				m_NewDir.y = 0;

				return;
			}
		}

		if (canGoLeft)
		{
			m_NewDir.x = -1;
			m_NewDir.y = 0;

			return;
		}

		if (canGoRight)
		{
			m_NewDir.x = 1;
			m_NewDir.y = 0;

			return;
		}

		if (canGoDown)
		{
			m_NewDir.x = 0;
			m_NewDir.y = 1;
		}

		if (canGoDown)
		{
			m_NewDir.x = 0;
			m_NewDir.y = -1;
		}

	}

}
