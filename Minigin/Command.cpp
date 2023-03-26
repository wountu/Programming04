#include "Command.h"
#include "TransformComponent.h"
#include "TimeClass.h"

namespace dae
{
	Movement::Movement(GameObject* pActor)
		:Command(pActor)
	{
		m_pTransform = pActor->GetComponent<TransformComponent>();
	}

	Movement::~Movement()
	{
		//delete m_pTransform;
		//m_pTransform = nullptr;
	}

	void Movement::Execute()
	{
		auto& timeClass = TimeClass::GetInstance();
		glm::vec2 newPos{ m_pTransform->GetPosition() + (m_Direction * m_Speed * timeClass.GetElapsed()) };
		m_pTransform->ChangePosition(newPos);
	}
}