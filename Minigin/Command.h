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


	class MovementRight : public Command
	{
	public:
		MovementRight(GameObject* pTransform);
		void Execute() override;

		void SetDirectionAndSpeed(glm::vec2 dir, float speed) { m_Direction = dir, m_Speed = speed; }
	private:
		TransformComponent* m_pTransform{ nullptr };
		glm::vec2 m_Direction{};
		float m_Speed{};
	};
}


