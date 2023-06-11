#pragma once
#include "GameObject.h"
#include "glm/vec2.hpp"

namespace dae
{
	class TransformComponent;

	class Command
	{
	public:
		Command() = default;
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};


	class Movement : public Command
	{
	public:
		Movement(GameObject* pTransform);
		virtual ~Movement();

		void Execute() override;

		void SetDirectionAndSpeed(glm::vec2 dir, float speed) { m_Direction = dir, m_Speed = speed; }
	private:
		//std::shared_ptr<TransformComponent> m_pTransform{ nullptr };
		std::shared_ptr<TransformComponent> m_pTransform{ nullptr };
		glm::vec2 m_Direction{};
		float m_Speed{};
		GameObject* m_Parent{ nullptr };
	};

	class Shoot final : public Command
	{
	public:
		Shoot(GameObject* parent);
		virtual ~Shoot() = default;

		void Execute() override;
		void SetDirection(glm::vec2 dir);
	private:
		GameObject* m_Parent{ nullptr };
		glm::vec2 m_Direction{};
	};

	class Damage final : public Command
	{
	public:
		Damage(GameObject* parent);
		virtual ~Damage() = default;

		void Execute() override;
	private:
		GameObject* m_Parent{ nullptr };
	};

	class Score final : public Command
	{
	public:
		Score(GameObject* parent);
		virtual ~Score() = default;

		void Execute() override;
	private:
		GameObject* m_Parent{ nullptr };
	};

	class Gamemode;
	class NextGamemode final : public Command
	{
	public:
		NextGamemode(GameObject* parent);
		virtual ~NextGamemode() = default;

		void Execute() override;
	private:
		GameObject* m_Parent{};
	};

	class Start final : public Command
	{
	public:
		Start(GameObject* parent);
		virtual ~Start() = default;

		void Execute() override;
	private:
		GameObject* m_Parent;
	};
}


