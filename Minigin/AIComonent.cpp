#include "AIComonent.h"
#include "GameObject.h"
#include "VisionComponent.h"

#include "PlayerState.h"
#include "Move.h"
#include "Idle.h"
#include <memory>

dae::AIComponent::~AIComponent()
{
	delete m_PlayerState;
}

void dae::AIComponent::Initialize(float tankSpeed, std::shared_ptr<GameObject> parent)
{
	m_Parent = parent.get();
	m_Transform = m_Parent->GetComponent<TransformComponent>();
	m_Vision = m_Parent->GetComponent<VisionComponent>();
	m_TankSpeed = tankSpeed;

	auto idle = new Idle();
	idle->Initialize(1.f, this);
	m_PlayerState = idle;
	m_PlayerState->OnEnter();
}

void dae::AIComponent::Update()
{
	auto newState = m_PlayerState->HandleInput();
	if (newState != nullptr)
	{
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

float dae::AIComponent::GetTankSpeed() const
{
	return m_TankSpeed;
}
