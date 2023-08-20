#include "CollisionDetector.h"

void dae::CollisionDetector::AddCollisionBox(CollisionBoxComponent* box, Tag tag)
{
	switch (tag)
	{
	case dae::Static:
		m_pWallBoxes.emplace_back(box);
		break;
	default:
		m_pPlayerCollisions.emplace_back(box);
		break;
	}
}

void dae::CollisionDetector::RemoveCollisionBox(CollisionBoxComponent* box)
{
	if (box->GetParent()->GetTag() == dae::Static)
		m_pWallBoxes.erase(std::remove(m_pWallBoxes.begin(), m_pWallBoxes.end(), box), m_pWallBoxes.end());

	else m_pPlayerCollisions.erase(std::remove(m_pPlayerCollisions.begin(), m_pPlayerCollisions.end(), box), m_pPlayerCollisions.end());
}

std::vector<dae::CollisionBoxComponent*> dae::CollisionDetector::GetCollisionBoxes() const
{
	return m_pWallBoxes;
}

dae::CollisionBoxComponent* dae::CollisionDetector::BoxColliding(CollisionBoxComponent* boxToCheck, dae::Tag ignores)
{
	if (ignores != Tag::Static)
	{
		for (const auto& boxComp : m_pWallBoxes)
		{
			if (boxComp == boxToCheck || !boxComp->GetParent()->GetActive() || !boxComp->IsActive())
				continue;

			auto box = boxComp->GetBox();
			auto otherBox = boxToCheck->GetBox();

			glm::vec2 rightBottomBox = { box._leftTop.x + box._width, box._leftTop.y + box._height };
			glm::vec2 rightBottomOtherBox = { otherBox._leftTop.x + otherBox._width, otherBox._leftTop.y + otherBox._height };

			if (box._leftTop.x >= rightBottomOtherBox.x || otherBox._leftTop.x >= rightBottomBox.x || box._leftTop.y >= rightBottomOtherBox.y || otherBox._leftTop.y >= rightBottomBox.y)
				continue;

			return boxComp;
		}
	}

	for (const auto& boxComp : m_pPlayerCollisions)
	{
		if (boxComp == boxToCheck || !boxComp->IsActive())
			continue;

		auto box = boxComp->GetBox();
		auto otherBox = boxToCheck->GetBox();

		glm::vec2 rightBottomBox = { box._leftTop.x + box._width, box._leftTop.y + box._height };
		glm::vec2 rightBottomOtherBox = { otherBox._leftTop.x + otherBox._width, otherBox._leftTop.y + otherBox._height };

		//if(rightBottomOtherBox.x )

		//if (std::abs(box._leftTop.x - otherBox._leftTop.x) >= 100)
		//	continue;
		//if (std::abs(box._leftTop.y - otherBox._leftTop.y) >= 100)
		//	continue;

		if (box._leftTop.x >= rightBottomOtherBox.x || otherBox._leftTop.x >= rightBottomBox.x || box._leftTop.y >= rightBottomOtherBox.y || otherBox._leftTop.y >= rightBottomBox.y)
			continue;

		return boxComp;
	}

	return nullptr;
}

std::vector<dae::CollisionBoxComponent*> dae::CollisionDetector::BoxesCollidingWithRay(glm::vec2 startRay, glm::vec2 endRay, glm::vec2 dir)
{
	std::vector<CollisionBoxComponent*> seenBoxes;

	for (const auto& boxComp : m_pWallBoxes)
	{
		if (!boxComp->IsActive())
			continue;
		const auto box = boxComp->GetBox();

		//Left
		if (dir.x == -1 && endRay.x < box._leftTop.x && startRay.x > box._leftTop.x)
		{
			if (startRay.y > box._leftTop.y && startRay.y < box._leftTop.y + box._height)
				seenBoxes.push_back(boxComp);
		}

		//Top
		if (dir.y == -1 && endRay.y < box._leftTop.y && startRay.y > box._leftTop.y)
		{
			if (startRay.x > box._leftTop.x && startRay.x < box._leftTop.x + box._width)
				seenBoxes.push_back(boxComp);
		}

		//Right
		if (dir.x == 1 && endRay.x > box._leftTop.x && startRay.x < box._leftTop.x)
		{
			if (startRay.y > box._leftTop.y && startRay.y < box._leftTop.y + box._height)
				seenBoxes.push_back(boxComp);
		}

		//Bot
		if(dir.y == 1 && endRay.y > box._leftTop.y && startRay.y < box._leftTop.y)
		{
			if (startRay.x > box._leftTop.x && startRay.x < box._leftTop.x + box._width)
				seenBoxes.push_back(boxComp);
		}
	}

	for (const auto& playerColl : m_pPlayerCollisions)
	{
		if (!playerColl->IsActive())
			continue;
		const auto box = playerColl->GetBox();

		//Left
		if (dir.x == -1 && endRay.x < box._leftTop.x && startRay.x > box._leftTop.x)
		{
			if (startRay.y > box._leftTop.y && startRay.y < box._leftTop.y + box._height)
				seenBoxes.push_back(playerColl);
		}

		//Top
		if (dir.y == -1 && endRay.y < box._leftTop.y && startRay.y > box._leftTop.y)
		{
			if (startRay.x > box._leftTop.x && startRay.x < box._leftTop.x + box._width)
				seenBoxes.push_back(playerColl);
		}

		//Right
		if (dir.x == 1 && endRay.x > box._leftTop.x && startRay.x < box._leftTop.x)
		{
			if (startRay.y > box._leftTop.y && startRay.y < box._leftTop.y + box._height)
				seenBoxes.push_back(playerColl);
		}

		//Bot
		if (dir.y == 1 && endRay.y > box._leftTop.y && startRay.y < box._leftTop.y)
		{
			if (startRay.x > box._leftTop.x && startRay.x < box._leftTop.x + box._width)
				seenBoxes.push_back(playerColl);
		}
	}

	return seenBoxes;
}
