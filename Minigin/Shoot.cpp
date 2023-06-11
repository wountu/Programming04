#include "Shoot.h"
#include "Move.h"
#include "VisionComponent.h"

void dae::ShootAI::Initialize(AIComponent* ai)
{
	m_AI = ai;
	m_BulletManager = m_AI->GetBulletManager();
}

void dae::ShootAI::OnEnter()
{
}

dae::PlayerState* dae::ShootAI::HandleInput()
{
	m_BulletManager->SpawnBullet(m_AI->GetVision()->GetDirection());

	auto move = new Move();
	move->Initialize(m_AI, m_AI->GetTransform(), m_AI->GetVision(), m_AI->GetTankSpeed());
	return move;
}

void dae::ShootAI::OnExit()
{
	m_AI->Shot();
}
