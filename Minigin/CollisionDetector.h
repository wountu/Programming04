#pragma once
#include "Singleton.h"
#include "CollisionBoxComponent.h"
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

		void AddCollisionBox(CollisionBoxComponent* box);
		void RemoveCollisionVox(CollisionBoxComponent* box);

		std::vector<CollisionBoxComponent*> GetCollisionBoxes() const;

		CollisionBoxComponent* BoxColliding(CollisionBoxComponent* boxToCheck);
	private:
		std::vector<CollisionBoxComponent*> m_pCollisionBoxes;
	};
}
