#include <string>
#include <vector>

#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Achievement.h"

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
	m_parent = parent;
	if (m_parent)
		m_parent->AddChild(this);
}

size_t dae::GameObject::GetChildCount() const
{
	return m_children.size();
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAt(int idx) const
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

void dae::GameObject::Update()
{
	for (std::shared_ptr<BaseComponent> pComponent : m_components)
	{
		pComponent->Update();
	}

	//Updating observers
	if (m_Subject)
	{
		m_Subject->Update();
		//m_Subject->NotifyObserver(this, dae::Observer::Event::PLAYER_DIED);
	}

}

void dae::GameObject::Render() const
{
	for (std::shared_ptr<BaseComponent> pComponent : m_components)
	{
		pComponent->Render();
	}

	//Rendering observers
	if (m_Subject)
	{
		m_Subject->Render();
	}
}

