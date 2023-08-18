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

dae::State* dae::Idle::Update()
{
	m_TimeIdle += TimeClass::GetInstance().GetElapsed();
	if (m_TimeIdle > m_TimeBeingIdle)
	{
		const float speed{ 50.f };
		auto move = new Move();
		move->Initialize(m_AI, speed);
		return move;
	}
	return nullptr;
}

void dae::Idle::OnExit()
{
}
