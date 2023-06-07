#include <memory>

#include "BaseComponent.h"
#include "TransformComponent.h"
#include "TextObject.h"
#include "Texture2D.h"

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

		void SpawnBullet(glm::vec2 dir);
	private:
		GameObject* m_Parent{ nullptr };
		TransformComponent* m_Transform{ nullptr };

		std::shared_ptr<Texture2D> m_Texture{ nullptr };

		std::vector<std::shared_ptr<GameObject>> m_pBullets;
	};
}
