#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"
#include "TransformComponent.h"
#include "LevelGenerator.h"

namespace dae
{
	class PlayerComponent final : public BaseComponent
	{
	public:
		PlayerComponent() = default;
		virtual ~PlayerComponent();
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;
		
		virtual void Initialize(std::shared_ptr<GameObject> parent, const float movementSpeed);
		virtual void Update() override;

		void SetDirection(glm::vec2 dir);
		
		bool CanGoLeft(int idx);
		bool CanGoRight(int idx);
		bool CanGoUp(int idx);
		bool CanGoDown(int idx);
	private:
		bool CheckUpcomingCollision();

		glm::vec2 m_Direction{};
		std::shared_ptr<TransformComponent> m_Transform{};
		std::shared_ptr<Texture2D> m_Texture{};

		int m_GridWidth;
		int m_GridHeight;

		std::vector<Tile> m_Grid{};

		float m_MovementSpeed{};
	};
}


