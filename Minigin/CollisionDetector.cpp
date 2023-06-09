#include "CollisionDetector.h"

void dae::CollisionDetector::AddCollisionBox(CollisionBoxComponent* box, Tag tag)
{
	switch (tag)
	{
	case dae::Static:
		m_pWallBoxes.emplace_back(box);
		break;
	default:
		m_pTankCollisions.emplace_back(box);
		break;
	}
}

void dae::CollisionDetector::RemoveCollisionVox(CollisionBoxComponent* box)
{
	m_pWallBoxes.erase(std::remove(m_pWallBoxes.begin(), m_pWallBoxes.end(), box), m_pWallBoxes.end());
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
			if (boxComp == boxToCheck)
				continue;


			auto box = boxComp->GetBox();
			auto otherBox = boxToCheck->GetBox();

			glm::vec2 rightBottomBox = { box._leftTop.x + box._width, box._leftTop.y + box._height };
			glm::vec2 rightBottomOtherBox = { otherBox._leftTop.x + otherBox._width, otherBox._leftTop.y + otherBox._height };

			//if (std::abs(box._leftTop.x - otherBox._leftTop.x) >= 100)
			//	continue;
			//if (std::abs(box._leftTop.y - otherBox._leftTop.y) >= 100)
			//	continue;

			if (box._leftTop.x >= rightBottomOtherBox.x || otherBox._leftTop.x >= rightBottomBox.x || box._leftTop.y >= rightBottomOtherBox.y || otherBox._leftTop.y >= rightBottomBox.y)
				continue;

			return boxComp;
		}
	}

	for (const auto& boxComp : m_pTankCollisions)
	{
		if (boxComp == boxToCheck)
			continue;


		auto box = boxComp->GetBox();
		auto otherBox = boxToCheck->GetBox();

		glm::vec2 rightBottomBox = { box._leftTop.x + box._width, box._leftTop.y + box._height };
		glm::vec2 rightBottomOtherBox = { otherBox._leftTop.x + otherBox._width, otherBox._leftTop.y + otherBox._height };

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
