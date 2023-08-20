#include "PlayerComponent.h"
#include "GameObject.h"
#include "TimeClass.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "Scene.h"


dae::PlayerComponent::~PlayerComponent()
{
}

void dae::PlayerComponent::Initialize(std::shared_ptr<GameObject> parent, const float movementSpeed)
{
	m_Texture = parent->GetComponent<RenderComponent>()->GetTexture();
	m_Transform = parent->GetComponent<TransformComponent>();
	m_MovementSpeed = movementSpeed;

	auto grids = GridGenerator::GetInstance().GetGrid();
	m_Grid = grids[SceneManager::GetInstance().GetActiveScene()->GetLevelName()];

	assert(!m_Grid.empty() && "The player needs the grid to be generated before creating the player(playercomponent)");

	m_GridHeight = GridGenerator::GetInstance().GetGridHeight();
	m_GridWidth = GridGenerator::GetInstance().GetGridWidth();

	m_Collision = parent->GetComponent<dae::CollisionBoxComponent>().get();
	m_Health = parent->GetComponent<dae::HealthComponent>().get();
	
	m_PlayersTag = parent->GetTag();
}

void dae::PlayerComponent::Render() const
{
}

void dae::PlayerComponent::Update()
{
	m_Transform->ChangeLocalPosition(m_Transform->GetWorldPosition() +
		(m_Direction * m_MovementSpeed * TimeClass::GetInstance().GetElapsed()));

	if (m_NewDirection != m_Direction && CheckForTurn()) //Needs to turn when arrived at the middle of the tile
	{
		Turn();
	}

	if (CheckUpcomingCollision() && CheckForTurn())
	{
		m_Direction.x = 0;
		m_Direction.y = 0;
	}

	auto overlap = m_Collision->GetOverlappingGameObject();

	if (m_PlayersTag == dae::Player1)
	{
		if (overlap && overlap->GetTag() == dae::Enemy)
		{
			std::cout << "Enemyoverlapped\n";
			m_Health->LoseHealth();
		}
	}

	if (m_PlayersTag == dae::Enemy)
	{
		if (overlap && overlap->GetTag() == dae::Player1)
		{
			overlap->GetComponent<dae::HealthComponent>()->LoseHealth();
		}
	}
}

void dae::PlayerComponent::HandleEvent(GameObject*, Event event)
{
	if (event == dae::Observer::Level_Next)
	{
		m_Grid = GridGenerator::GetInstance().GetGrid()[SceneManager::GetInstance().GetActiveScene()->GetLevelName()];
		m_NewDirection = { 0, 0 };
		m_Direction = { 0, 0 };
	}
}

void dae::PlayerComponent::OnSubjectDestroy()
{
}

void dae::PlayerComponent::SetDirection(glm::vec2 dir)
{
	if (m_Direction == dir)
		return;

	auto& gridGen = GridGenerator::GetInstance();

	auto pos = m_Transform->GetWorldPosition();
	pos.x += m_Texture->GetSize().x / 2.f;
	pos.y += m_Texture->GetSize().y / 2.f;

	int idx = gridGen.GetIdxFromPos(pos);
	//const int gridWidth{  };
	//const int gridHeight{ gridGen.GetGridHeight() };

	if (dir.x == -1 && CanGoLeft(idx))
	{
		m_NewDirection = dir;
		//m_Transform->SetDirection(m_Direction);
	}

	if (dir.x == 1 && CanGoRight(idx))
	{
		m_NewDirection = dir;
		//m_Transform->SetDirection(m_Direction);
	}

	if (dir.y == 1 && CanGoDown(idx))
	{
		m_NewDirection = dir;
		//m_Transform->SetDirection(m_Direction);
	}

	if (dir.y == -1 && CanGoUp(idx))
	{
		m_NewDirection = dir;
		//m_Transform->SetDirection(m_Direction);
	}
}

bool dae::PlayerComponent::CanGoLeft(int idx)
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

bool dae::PlayerComponent::CanGoRight(int idx) 
{
	int rightIdx{};
	if ((idx + 1) % m_GridWidth <= m_GridWidth && idx + 1 > 0)
	{
		rightIdx = idx + 1;

		if (m_Grid[rightIdx].walkable)
			return true;

	}

	return false;
}

bool dae::PlayerComponent::CanGoUp(int idx)
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

bool dae::PlayerComponent::CanGoDown(int idx)
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

bool dae::PlayerComponent::CheckUpcomingCollision()
{
	auto pos = m_Transform->GetWorldPosition();
	pos.x += m_Texture->GetSize().x / 2.f;
	pos.y += m_Texture->GetSize().y / 2.f;

	int idx = GridGenerator::GetInstance().GetIdxFromPos(pos);

	if (m_Direction.x == 1)
	{
		if (CanGoRight(idx))
			return false;
		else return true;
	}

	if (m_Direction.x == -1)
	{
		if (CanGoLeft(idx))
			return false;
		else return true;
	}

	if (m_Direction.y == -1)
	{
		if (CanGoUp(idx))
			return false;
		else return true;
	}

	if (m_Direction.y == 1)
	{
		if (CanGoDown(idx))
			return false;
		else return true;
	}

	return false;
}

bool dae::PlayerComponent::CheckForTurn()
{
	const int turnRadius{ 1 }; //The radius the player can be from the turning point to turn in

	auto pos = m_Transform->GetWorldPosition(); //Players pos

	glm::vec2 middlePos{ pos }; // To find the right tile he is standing on
	middlePos.x += m_Texture->GetSize().x / 2.f;
	middlePos.y += m_Texture->GetSize().y / 2.f;

	//Find the right tile
	int idx = GridGenerator::GetInstance().GetIdxFromPos(middlePos);
	dae::Tile node = m_Grid[idx];

	//Middle point of turning node
	glm::vec2 nodeMiddle{};
	nodeMiddle.x = node.LeftTop.x + node.Width / 2.f;
	nodeMiddle.y = node.LeftTop.y + node.Height / 2.f;

	float dist = glm::distance(middlePos, nodeMiddle);

	if (dist < turnRadius)
	{
		return true;
	}
	
	return false;
}

void dae::PlayerComponent::Turn()
{
	m_Direction = m_NewDirection;
	m_Transform->SetDirection(m_Direction);
}
