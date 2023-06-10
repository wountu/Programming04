#pragma once
#include "Singleton.h"
#include "CollisionBoxComponent.h"
#include "GameObject.h"

class CollisionBoxComponent;
namespace dae
{
	class CollisionDetector final : public Singleton<CollisionDetector>
	{
	public:
		CollisionDetector() = default;
		virtual ~CollisionDetector() = default;
		CollisionDetector(const CollisionDetector& other) = delete;
		CollisionDetector& operator=(const CollisionDetector& other) = delete;
		CollisionDetector(CollisionDetector&& other) = delete;
		CollisionDetector& operator=(CollisionDetector&& other) = delete;

		void AddCollisionBox(CollisionBoxComponent* box, Tag tag);
		void RemoveCollisionVox(CollisionBoxComponent* box);

		std::vector<CollisionBoxComponent*> GetCollisionBoxes() const;

		CollisionBoxComponent* BoxColliding(CollisionBoxComponent* boxToCheck, Tag ignores);

		CollisionBoxComponent* BoxCollidingWithRay(glm::vec2 startRay, glm::vec2 endRay, glm::vec2 dir);

	private:
		std::vector<CollisionBoxComponent*> m_pTankCollisions;
		std::vector<CollisionBoxComponent*> m_pWallBoxes;
	};
}
