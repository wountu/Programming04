#pragma once
#include <memory>
#include <glm/vec2.hpp>

#include "BaseComponent.h"

namespace dae
{
	struct CollisionBox
	{
		CollisionBox() = default;

		CollisionBox(glm::vec2 leftTop, float width, float height)
		{
			_leftTop = leftTop;
			_width = width;
			_height = height;
		}

		glm::vec2 _leftTop{};
		float _width{};
		float _height{};
	};

	class TransformComponent;
	class CollisionBoxComponent final : public BaseComponent
	{
	public:
		CollisionBoxComponent() = default;
		virtual ~CollisionBoxComponent() = default;
		CollisionBoxComponent(const CollisionBoxComponent& other)			 = delete;
		CollisionBoxComponent& operator=(const CollisionBoxComponent& other) = delete;
		CollisionBoxComponent(CollisionBoxComponent&& other)				 = delete;
		CollisionBoxComponent& operator =(CollisionBoxComponent&& other)	 = delete;

		virtual void Initialize(std::shared_ptr<GameObject> parent, CollisionBox collision, int inset);
		virtual void Update() override;
		virtual void Render() const override;
		
		void CheckCollision();

		CollisionBox GetBox() const;
		GameObject* GetOverlappingGameObject();

		GameObject* GetParent() const;
	private:
		GameObject* m_Parent{ nullptr };
		GameObject* m_CollidingObject{};
		CollisionBox m_CollisionBox{};
		std::shared_ptr<TransformComponent> m_Transform{};

		int m_Inset{}; //How much the box needs to inset to the given collisionbox
	};
}
