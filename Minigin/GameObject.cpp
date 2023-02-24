#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(){}

void dae::GameObject::Render() const
{
	//const auto& pos = m_transform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

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

template<typename T>
std::shared_ptr<T> dae::GameObject::GetComponent() const
{
	//std::shared_ptr component = std::make_shared<T>();

	return nullptr;
}

template<typename T>
void dae::GameObject::RemoveComponent()
{
}


