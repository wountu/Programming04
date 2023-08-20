#pragma once
#include "State.h"
#include "AIComonent.h"
#include "GridGenerator.h"

#include <glm/vec2.hpp>
#include <memory>
#include <deque>

namespace dae
{
	class TransformComponent;
	class VisionComponent;
	class Move final : public State
	{
	public:
		Move() = default;
		virtual ~Move() = default;

		Move(const Move& other) = delete;
		Move& operator=(const Move& other) = delete;
		Move(Move&& other) = delete;
		Move& operator =(Move&& other) = delete;

		void Initialize(AIComponent* ai, float speed);

		virtual void OnEnter() override;
		virtual State* Update() override;
		virtual void OnExit() override;
	private:
		std::shared_ptr<TransformComponent> m_Transform{};
		VisionComponent* m_Vision{};
		AIComponent* m_AI{};

		glm::vec2 m_Dir{};
		glm::vec2 m_NewDir{};
		float m_Speed{};
		bool m_MovingAlongX{ false };

		int m_GridWidth{};
		int m_GridHeight{};
		std::vector<Tile> m_Grid{};

		int m_CurrentTileIdx{};
		int m_LastTileIdx{};
		glm::vec2 m_LastDir{};
		std::deque<int> m_LastTiles{};
		const size_t m_NmbrOfTilesToKeep{ 50 };

		bool CanGoLeft(int idx);
		bool CanGoRight(int idx);
		bool CanGoUp(int idx);
		bool CanGoDown(int idx);
		
		void CheckCollision();
		void LookForNewDir();

		bool CheckForTurn();
		void CheckIfUpcomingTyleVisitedRecently(bool canGoLeft, bool canGoRight, bool canGoUp, bool canGoDown);
	};
}

