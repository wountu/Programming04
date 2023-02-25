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
	//const auto& pos = m_transform.GetPosition();
	//assert((m_pTransform != nullptr) && ("GameObject needs a transformcomponent attached to it to render it"));

	for (std::shared_ptr<BaseComponent> pComponent : m_components)
	{
		//Renderer::GetInstance().SetRenderPos(m_pTransform->GetPosition());
		pComponent->Render();
	}

	//Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

//void dae::GameObject::SetTexture(const std::string& filename)
//{
//	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
//}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

//template<typename T>
//void dae::GameObject::AddComponent(std::shared_ptr<T> otherComponent)
//{
//	//return nullptr;
//}

//template<typename T>
//std::shared_ptr<T> dae::GameObject::AddComponent()
//{
//
//}

//template<typename T>
//std::shared_ptr<T> dae::GameObject::GetComponent() const
//{
//	
//
//	return nullptr;
//}

template<typename T>
void dae::GameObject::RemoveComponent()
{
}


