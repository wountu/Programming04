#include "BaseComponent.h"

namespace dae
{
	void BaseComponent::Initialize(std::shared_ptr<GameObject> parent)
	{
		m_pParent = parent.get();
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
