#include "AIComonent.h"
#include "GameObject.h"
#include "VisionComponent.h"
#include "TimeClass.h"

#include "PlayerState.h"
#include "Move.h"
#include "Idle.h"
#include <memory>

dae::AIComponent::~AIComponent()
{
	delete m_PlayerState;
}

void dae::AIComponent::Initialize(float tankSpeed, std::shared_ptr<GameObject> parent, std::shared_ptr<BulletManager> bulletManager)
{
	m_Parent = parent.get();
	m_Transform = m_Parent->GetComponent<TransformComponent>();
	m_Vision = m_Parent->GetComponent<VisionComponent>();
	m_TankSpeed = tankSpeed;

	auto idle = new Idle();
	idle->Initialize(1.f, this);
	m_PlayerState = idle;
	m_PlayerState->OnEnter();

	m_BulletManager = bulletManager;
}

void dae::AIComponent::Update()
{
	if (m_TimeSinceLastBullet <= m_TimeInBetweenBullets)
	{
		m_TimeSinceLastBullet += TimeClass::GetInstance().GetElapsed();
		m_CanShoot = false;
	}
	else m_CanShoot = true;

	auto newState = m_PlayerState->HandleInput();
	if (newState != nullptr)
	{
		m_PlayerState->OnExit();
		delete m_PlayerState;
		m_PlayerState = newState;
		m_PlayerState->OnEnter();
	}
}

void dae::AIComponent::Render() const
{
}

std::shared_ptr<dae::TransformComponent> dae::AIComponent::GetTransform() const
{
	return m_Transform;
}

std::shared_ptr<dae::VisionComponent> dae::AIComponent::GetVision() const
{
	return m_Vision;
}

std::shared_ptr<dae::BulletManager> dae::AIComponent::GetBulletManager() const
{
	return m_BulletManager;
}

float dae::AIComponent::GetTankSpeed() const
{
	return m_TankSpeed;
}

glm::vec2 dae::AIComponent::GetTargetDir() const
{
	return m_TargerDir;
}

void dae::AIComponent::SetTargetDir(glm::vec2 targetDir)
{
	float dist = sqrt((targetDir.x * targetDir.x) + (targetDir.y * targetDir.y));
	targetDir /= dist;
	m_TargerDir = targetDir;
}

void dae::AIComponent::Shot()
{
	m_TimeSinceLastBullet = 0.f;
}

bool dae::AIComponent::GetCanShoot() const
{
	return m_CanShoot;
}
