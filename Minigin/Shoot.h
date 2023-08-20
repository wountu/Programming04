#pragma once
#include "State.h"
#include "AIComonent.h"

#include <glm/vec2.hpp>
#include <memory>

namespace dae
{
	class TransformComponent;
	class ShootAI final : public State
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
		virtual State* Update() override;
		virtual void OnExit() override;
	private:
		AIComponent* m_AI{ nullptr };
		std::shared_ptr<BulletManager> m_BulletManager{ nullptr };
	};
}

