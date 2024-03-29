#include "BaseComponent.h"

namespace dae
{
	void BaseComponent::Initialize(std::shared_ptr<GameObject> parent)
	{
		m_pParent = parent;
	}

	BaseComponent::~BaseComponent()
	{
		m_pParent.reset();
	}

	void BaseComponent::Update()
	{
	}

	void BaseComponent::Render() const
	{
	}
}
