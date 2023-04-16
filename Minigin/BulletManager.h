#include <memory>

#include "BaseComponent.h"
#include "TransformComponent.h"
#include "TextObject.h"

namespace dae
{
	class BulletManager final : public BaseComponent
	{
	public:
		BulletManager() = default;
		virtual ~BulletManager() = default;
		BulletManager(const BulletManager& other) = delete;
		BulletManager& operator=(const BulletManager& other) = delete;
		BulletManager(BulletManager&& other) = delete;
		BulletManager& operator =(BulletManager&& other) = delete;

		virtual void Initialize(std::shared_ptr<GameObject> parent);
		virtual void Update() override;
		virtual void Render() const override;

		void SpawnBullet(glm::vec2 pos, glm::vec2 dir);
	private:
		GameObject* m_Parent{ nullptr };
		TransformComponent* m_Transform{ nullptr };
		bool m_FirstFrame{ true };
	};
}
