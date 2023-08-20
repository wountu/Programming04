#include "AIComonent.h"
#include "GameObject.h"
#include "VisionComponent.h"
#include "TimeClass.h"

#include "State.h"
#include "Move.h"
#include "Idle.h"
#include <memory>

dae::AIComponent::~AIComponent()
{
	delete m_GhostState;
}

void dae::AIComponent::Initialize(std::shared_ptr<GameObject> parent)
{
	m_Parent = parent.get();
	m_Vision = m_Parent->GetComponent<dae::VisionComponent>().get();

	auto idle = new Idle();
	idle->Initialize(1.f, this);	
	m_GhostState = idle;
	m_GhostState->OnEnter();
}

void dae::AIComponent::Update()
{
	auto newState = m_GhostState->Update();
	if (newState != nullptr)
	{
		m_GhostState->OnExit();
		delete m_GhostState;
		m_GhostState = newState;
		m_GhostState->OnEnter();
	}
}

void dae::AIComponent::Render() const
{
}

dae::GameObject* dae::AIComponent::GetParent() const
{
	return m_Parent;
}

dae::VisionComponent* dae::AIComponent::GetVision() const
{
	return m_Vision;
}
