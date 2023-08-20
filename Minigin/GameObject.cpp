#include <string>
#include <vector>

#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "SceneManager.h"
#include "Scene.h"

#include "CollisionDetector.h"

void dae::GameObject::Initialize()
{
	m_pTransform = GetComponent<TransformComponent>();
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_parent;
}

void dae::GameObject::SetParent(std::shared_ptr<GameObject> parent, bool keepWorldPos)
{
	if (parent == nullptr)
		m_pTransform->ChangeLocalPosition(m_pTransform->GetWorldPosition());

	else
	{
		if (keepWorldPos)
		{
			m_pTransform->ChangeLocalPosition(m_pTransform->GetLocalPosition() - parent->GetComponent<TransformComponent>()->GetWorldPosition());
		}
	}

	if (m_parent)
		m_parent->RemoveChild(std::shared_ptr<GameObject>(this));
	m_parent = parent.get();
	if (m_parent)
		m_parent->AddChild(this);
}

void dae::GameObject::AddChild(GameObject* pChild)
{
	m_children.emplace_back(pChild);
}

std::vector<dae::GameObject*> dae::GameObject::GetChildren() const
{
	return m_children;
}

void dae::GameObject::RemoveChild(std::shared_ptr<GameObject> child)
{
	auto result = std::find(m_children.begin(), m_children.end(), child.get());

	if (result != m_children.end())
	{
		m_children.erase(std::remove(m_children.begin(), m_children.end(), child.get()), m_children.end());
	}
}

void dae::GameObject::SetPositionDirty()
{
	m_positionIsDirty = true;
}

void dae::GameObject::SetLocalPos(const glm::vec2& pos)
{
	m_localPos = pos;
	SetPositionDirty();
}

void dae::GameObject::UpdateWorldPos()
{
	if (m_positionIsDirty)
	{
		if (m_parent == nullptr)
			m_worldPos = m_localPos;
		else m_worldPos = m_parent->GetWorldPos() + m_localPos;
	}
	m_positionIsDirty = false;
}

const glm::vec2& dae::GameObject::GetWorldPos()
{
	if (m_positionIsDirty)
		UpdateWorldPos();
	return m_worldPos;
}

void dae::GameObject::SetTag(Tag tag)
{
	m_Tag = tag;
}

dae::Tag dae::GameObject::GetTag() const
{
	return m_Tag;
}

void dae::GameObject::SetActive(bool active)
{
	m_Active = active;

	for (auto& child : m_children)
	{
		child->SetActive(active);
	}
}

bool dae::GameObject::GetActive() const
{
	return m_Active;
}

void dae::GameObject::Destroy()
{
	auto coll = GetComponent<CollisionBoxComponent>();
	if (coll)
	{
		coll->SetActive(false);
	}

	m_destroy = true;
}

bool dae::GameObject::ShouldDestroy() const
{
	return m_destroy;
}

void dae::GameObject::Update()	
{
	if(m_Active)
	{
		for (std::shared_ptr<BaseComponent> pComponent : m_components)
		{
			pComponent->Update();
		}

		for (const auto& child : m_children)
		{
			child->Update();
		}
	}
}

void dae::GameObject::Render() const
{
	if(m_Active)
	{
		for (std::shared_ptr<BaseComponent> pComponent : m_components)
		{
			pComponent->Render();
		}

		for (const auto& child : m_children)
		{
			child->Render();
		}
	}
}

void dae::GameObject::RemoveAllComponents()
{
	for(auto& component : m_components)
	{
		component.reset();
	}
}

dae::GameObject::~GameObject()
{	
	m_children.clear();
}

