#pragma once
#include "PlayerState.h"
#include "AIComonent.h"
#include "BulletManager.h"

#include <glm/vec2.hpp>
#include <memory>

namespace dae
{
	class TransformComponent;
	class ShootAI final : public PlayerState
	{
	public:
		ShootAI() = default;
		virtual ~ShootAI() = default;

		ShootAI(const ShootAI& other) = delete;
		ShootAI& operator=(const ShootAI& other) = delete;
		ShootAI(ShootAI&& other) = delete;
		ShootAI& operator =(ShootAI&& other) = delete;

		void Initialize(AIComponent* ai);

		virtual void OnEnter() override;
		virtual PlayerState* HandleInput() override;
		virtual void OnExit() override;
	private:
		AIComponent* m_AI{ nullptr };
		std::shared_ptr<BulletManager> m_BulletManager{ nullptr };
	};
}

