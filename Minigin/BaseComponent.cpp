#include "BaseComponent.h"

namespace dae
{
	void BaseComponent::Initialize(std::shared_ptr<GameObject> parent)
	{
		m_Parent = parent;
	}

	BaseComponent::~BaseComponent()
	{
	}

	void BaseComponent::Update()
	{
	}

	void BaseComponent::Render() const
	{
	}
}
