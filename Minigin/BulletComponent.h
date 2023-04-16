#include <memory>

#include "BaseComponent.h"
#include "TransformComponent.h"
#include "TextObject.h"

namespace dae
{
	class BulletComponent final : public BaseComponent
	{
	public:
		BulletComponent() = default;
		virtual ~BulletComponent() = default;
		BulletComponent(const BulletComponent& other) = delete;
		BulletComponent& operator=(const BulletComponent& other) = delete;
		BulletComponent(BulletComponent&& other) = delete;
		BulletComponent& operator =(BulletComponent && other) = delete;

		virtual void Initialize(std::shared_ptr<GameObject> parent, glm::vec2 direction);
		virtual void Update() override;
		virtual void Render() const override;
	private:
		GameObject* m_Parent{ nullptr };
		TransformComponent* m_Transform{ nullptr };
		bool m_FirstFrame{ true };

		glm::vec2 m_Direction;
	};
}
