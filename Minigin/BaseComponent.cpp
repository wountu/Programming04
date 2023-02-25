#include "BaseComponent.h"

namespace dae
{
	void BaseComponent::Initialize()
	{
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

	bool BaseComponent::GetNeedUpdate() const
	{
		return m_needsUpdate;
	}

	bool BaseComponent::GetNeedRender() const
	{
		return m_needsRender;
	}

	void BaseComponent::SetOwner(std::weak_ptr<GameObject> parent)
	{
		m_Parent = parent;
	}
}
