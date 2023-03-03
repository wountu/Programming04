#include <string>
#include <vector>

#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (std::shared_ptr<BaseComponent> pComponent : m_components)
	{
		if (!pComponent->GetNeedUpdate())
			continue;

		pComponent->Update();
	}
}

void dae::GameObject::Render() const
{
	for (std::shared_ptr<BaseComponent> pComponent : m_components)
	{
		//Renderer::GetInstance().SetRenderPos(m_pTransform->GetPosition());
		pComponent->Render();
	}
}


void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}


