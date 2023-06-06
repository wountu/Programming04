#include <string>
#include <vector>

#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_parent;
}

void dae::GameObject::SetParent(std::shared_ptr<GameObject> parent, bool keepWorldPos)
{
	if (parent == nullptr)
		SetLocalPos(GetWorldPos());
	else
	{
		if (keepWorldPos)
			SetLocalPos(m_localPos - parent->GetWorldPos());
		SetPositionDirty();
	}

	if (m_parent)
		m_parent->RemoveChild(std::shared_ptr<GameObject>(this));
	m_parent = parent.get();
	if (m_parent)
		m_parent->AddChild(this);
}

size_t dae::GameObject::GetChildCount() const
{
	return m_children.size();
}

dae::GameObject* dae::GameObject::GetChildAt(int idx) const
{
	return m_children[idx];
}

void dae::GameObject::AddChild(GameObject* pChild)
{
	m_children.emplace_back(pChild);
}

void dae::GameObject::RemoveChild(std::shared_ptr<GameObject> child)
{

	//auto result = std::find(m_children.begin(), m_children.end(), child);

	//if (result != m_children.end())
	//{
	//	result->get()->SetParent(nullptr, true);

	//	m_children.erase(result);
	//}
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

void dae::GameObject::SetSubject(std::shared_ptr<Subject> subject)
{
	m_Subject = subject;
}

void dae::GameObject::NotifyObject(Observer::Event event)
{
	m_Subject->NotifyObserver(this, event);
}

void dae::GameObject::AddObserver(Observer* observer)
{
	m_Observers.push_back(observer);
}

void dae::GameObject::RemoverObservers(Observer* observer)
{
	m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer), m_Observers.end());
}

void dae::GameObject::NotifyObserver(GameObject* actor, Observer::Event event)
{
	for (const auto observer : m_Observers)
	{
		observer->Notify(actor, event);
	}
}

void dae::GameObject::SetTag(Tag tag)
{
	m_Tag = tag;
}

dae::Tag dae::GameObject::GetTag() const
{
	return m_Tag;
}

void dae::GameObject::Update()
{
	for (std::shared_ptr<BaseComponent> pComponent : m_components)
	{
		pComponent->Update();
	}

	for (const auto& child : m_children)
	{
		child->Update();
	}

	for (const auto& observer : m_Observers)
	{
		observer->Update();
	}
}

void dae::GameObject::Render() const
{
	for (std::shared_ptr<BaseComponent> pComponent : m_components)
	{
		pComponent->Render();
	}

	////Rendering observers
	//if (m_Subject)
	//{
	//	m_Subject->Render();
	//}

	for (const auto& observer : m_Observers)
	{
		observer->Render();
	}
}

