#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void dae::Scene::Activate()
{
	m_Active = true;

	for (const auto& object : m_objects)
	{
		object->SetActive(true);
		auto objectCol = object->GetComponent<CollisionBoxComponent>();
		if (objectCol)
			objectCol->SetActive(true);
	}
}

void dae::Scene::Deactivate()
{
	m_Active = false;

	for (const auto& object : m_objects)
	{
		object->SetActive(false);
		auto objectCol = object->GetComponent<CollisionBoxComponent>();
		if (objectCol)
			objectCol->SetActive(false);
	}
}

void Scene::Add(std::shared_ptr<GameObject> object)
{
	object->SetActive(m_Active);
	m_objects.emplace_back(std::move(object));
}

void dae::Scene::Add(std::vector<std::shared_ptr<GameObject>> objects)
{
	for (const auto& object : objects)
	{
		object->SetActive(m_Active);
		m_objects.emplace_back(std::move(object));
	}
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update()
{
	for(auto& object : m_objects)
	{
		object->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

