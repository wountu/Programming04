#include "Idle.h"
#include "Move.h"
#include "TimeClass.h"

#include <iostream>

//dae::Idle::~Idle()
//{
//	delete m_AI;
//	m_AI = nullptr;
//}

void dae::Idle::Initialize(float idleTime, AIComponent* ai)
{
	m_AI = ai;
	m_TimeBeingIdle = idleTime;
}

void dae::Idle::OnEnter()
{
}

dae::PlayerState* dae::Idle::HandleInput()
{
	m_TimeIdle += TimeClass::GetInstance().GetElapsed();
	if (m_TimeIdle > m_TimeBeingIdle)
	{
		auto move = new Move();
		move->Initialize(m_AI, m_AI->GetTransform(), m_AI->GetVision(), m_AI->GetTankSpeed());
		return move;
	}
	return nullptr;
}

void dae::Idle::OnExit()
{
}
