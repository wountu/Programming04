#include "CollisionDetector.h"

void dae::CollisionDetector::AddCollisionBox(CollisionBoxComponent* box)
{
	m_pCollisionBoxes.emplace_back(box);
}

void dae::CollisionDetector::RemoveCollisionVox(CollisionBoxComponent* box)
{
	m_pCollisionBoxes.erase(std::remove(m_pCollisionBoxes.begin(), m_pCollisionBoxes.end(), box), m_pCollisionBoxes.end());
}

std::vector<dae::CollisionBoxComponent*> dae::CollisionDetector::GetCollisionBoxes() const
{
	return m_pCollisionBoxes;
}

dae::CollisionBoxComponent* dae::CollisionDetector::BoxColliding(CollisionBoxComponent* boxToCheck)
{
	for (const auto& boxComp : m_pCollisionBoxes)
	{
		if (boxComp == boxToCheck)
			continue;

		auto box = boxComp->GetBox();
		auto otherBox = boxToCheck->GetBox();

		glm::vec2 rightBottomBox = { box._leftTop.x + box._width, box._leftTop.y + box._height };
		glm::vec2 rightBottomOtherBox = { otherBox._leftTop.x + otherBox._width, otherBox._leftTop.y + otherBox._height };

		if (box._leftTop.x >= rightBottomOtherBox.x || otherBox._leftTop.x >= rightBottomBox.x || box._leftTop.y >= rightBottomOtherBox.y || otherBox._leftTop.y >= rightBottomBox.y)
			continue;

		return boxComp;
	}
	return nullptr;
}
