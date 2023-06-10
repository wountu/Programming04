#include "AIComonent.h"
#include "GameObject.h"
#include "VisionComponent.h"

#include "PlayerState.h"
#include "Move.h"

dae::AIComponent::~AIComponent()
{
	delete m_PlayerState;
}

void dae::AIComponent::Initialize(float tankSpeed, std::shared_ptr<GameObject> parent)
{
	m_Parent = parent.get();
	m_Transform = m_Parent->GetComponent<TransformComponent>();
	m_Vision = m_Parent->GetComponent<VisionComponent>();

	m_PlayerState = new Move(m_Transform, m_Vision, tankSpeed);
	m_PlayerState->OnEnter();
}

void dae::AIComponent::Update()
{
	m_PlayerState->HandleInput();
}

void dae::AIComponent::Render() const
{
}
