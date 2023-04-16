#pragma once
#include "GameObject.h"
#include "glm/vec2.hpp"

namespace dae
{
	class TransformComponent;

	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
	protected:
		explicit Command(GameObject* pObject)
			:m_pObject{ pObject } {}

		GameObject* GetActor() const { return m_pObject; }
	private:
		GameObject* m_pObject{ nullptr };
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
	private:
		GameObject* m_Parent{ nullptr };
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
}


