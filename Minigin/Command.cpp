#include "Command.h"
#include "TransformComponent.h"
#include "TimeClass.h"
#include "Observer.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "BulletManager.h"

namespace dae
{
	//Movement
	Movement::Movement(GameObject* pActor)
		:Command(pActor)
	{
		m_pTransform = pActor->GetComponent<TransformComponent>();
		m_Parent = pActor;
	}

	Movement::~Movement()
	{
		//delete m_pTransform;
		//m_pTransform = nullptr;
	}

	void Movement::Execute()
	{
		auto& timeClass = TimeClass::GetInstance();
		glm::vec2 newPos{ m_pTransform->GetLocalPosition() + (m_Direction * m_Speed * timeClass.GetElapsed()) };
		m_pTransform->ChangeLocalPosition(newPos);
		m_pTransform->SetDirection(m_Direction);
	}

	Score::Score(GameObject* parent)
		:Command(parent)
	{
		m_Parent = parent;
	}

	void Score::Execute()
	{
		m_Parent->GetComponent<ScoreComponent>()->AddScore(100);
	}

	Shoot::Shoot(GameObject* parent)
		:Command(parent)
	{
		m_Parent = parent;
	}

	void Shoot::Execute()
	{
		m_Parent->GetComponent<BulletManager>()->SpawnBullet(m_Direction);

		float angle = static_cast<float>(atan2(m_Direction.y, m_Direction.x));
		angle = glm::degrees(angle);

		m_Parent->GetComponent<TransformComponent>()->ChangeAngle(angle);
	}
	void Shoot::SetDirection(glm::vec2 dir)
	{
		m_Direction = dir;
	}
}