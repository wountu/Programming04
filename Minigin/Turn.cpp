#include "Turn.h"
#include "Move.h"


#include "TransformComponent.h"


void dae::Turn::Initialize(AIComponent* ai, std::shared_ptr<TransformComponent> transform)
{
	m_AI = ai;
	m_Transform = transform;
}

void dae::Turn::OnEnter()
{
}

dae::State* dae::Turn::Update()
{
	//m_Transform->ChangeAngle(m_Transform->GetAngle() + 90.f);
	//
	//auto move = new Move();
	//move->Initialize(m_AI, m_AI->GetTransform(), m_AI->GetVision(), m_AI->GetTankSpeed());
	//return move;

	return nullptr;
}

void dae::Turn::OnExit()
{
}
