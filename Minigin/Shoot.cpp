#include "Shoot.h"
#include "Move.h"
#include "VisionComponent.h"

void dae::ShootAI::Initialize(AIComponent* ai)
{
	m_AI = ai;
}

void dae::ShootAI::OnEnter()
{
}

dae::State* dae::ShootAI::Update()
{
	return nullptr;
}

void dae::ShootAI::OnExit()
{
}
