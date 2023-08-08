#include "PlayerComponent.h"
#include "GameObject.h"
#include "TimeClass.h"
#include "RenderComponent.h"

dae::PlayerComponent::~PlayerComponent()
{
}

void dae::PlayerComponent::Initialize(std::shared_ptr<GameObject> parent, const float movementSpeed)
{
	m_Texture = parent->GetComponent<RenderComponent>()->GetTexture();
	m_Transform = parent->GetComponent<TransformComponent>();
	m_MovementSpeed = movementSpeed;

	m_Grid = GridGenerator::GetInstance().GetGrid();
	assert(!m_Grid.empty() && "The player needs the grid to be generated before creating the player(playercomponent)");

	m_GridHeight = GridGenerator::GetInstance().GetGridHeight();
	m_GridWidth = GridGenerator::GetInstance().GetGridWidth();
}

void dae::PlayerComponent::Update()
{
	m_Transform->ChangeLocalPosition(m_Transform->GetWorldPosition() +
		(m_Direction * m_MovementSpeed * TimeClass::GetInstance().GetElapsed()));

	if (CheckUpcomingCollision())
	{
		m_Direction.x = 0;
		m_Direction.y = 0;
	}
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
		m_Direction = dir;
		m_Transform->SetDirection(m_Direction);
	}

	if (dir.x == 1 && CanGoRight(idx))
	{
		m_Direction = dir;
		m_Transform->SetDirection(m_Direction);
	}

	if (dir.y == 1)
	{
		m_Direction = dir;
		m_Transform->SetDirection(m_Direction);
	}

	if (dir.y == -1)
	{
		m_Direction = dir;
		m_Transform->SetDirection(m_Direction);
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

	if (m_Direction.y == 1)
	{
		if (CanGoUp(idx))
			return false;
		else return true;
	}

	if (m_Direction.y == -1)
	{
		if (CanGoDown(idx))
			return false;
		else return true;
	}

	return false;
}
