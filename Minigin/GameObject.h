#pragma once
#include <memory>
#include <vector>
#include <iostream>
#include <string_view>
#include <glm/vec2.hpp>

#include "TransformComponent.h"
#include "Transform.h"
#include "BaseComponent.h"
#include "Observer.h"
#include "Subject.h"

namespace dae
{
	class Texture2D;
	//class BaseComponent;
	//class Observer;

	enum Tag
	{
		Static,
		Player1,
		Player2,
		Enemy
	};

	// todo: this should become final.
	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		//Update/Render
		void Update();
		void Render() const;

		//Components
		template <typename T> std::shared_ptr <T> AddComponent();
		template <typename T> std::shared_ptr <T> GetComponent() const;
		template <typename T> void RemoveComponent();
		void RemoveAllComponents();

		//Rule of 5
		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//Parents
		GameObject* GetParent() const;
		void SetParent(std::shared_ptr<GameObject> parent, bool keepWorldPos);
		
		//Children
		size_t GetChildCount() const;
		GameObject* GetChildAt(int idx) const;
		void RemoveChild(std::shared_ptr<GameObject> child);

		//positions
		void SetLocalPos(const glm::vec2& pos);
		const glm::vec2& GetWorldPos();

		//Set subject
		void SetSubject(std::shared_ptr<Subject> subject);
		void NotifyObject(Observer::Event event);

		//Observers
		void AddObserver(Observer* observer);
		void RemoverObservers(Observer* observer);
		void NotifyObserver(GameObject* actor, Observer::Event event);

		void SetTag(Tag tag);
		Tag GetTag() const;
	private:
		//Children
		void AddChild(GameObject* pChild);

		//Update position with dirty flag
		void SetPositionDirty();
		void UpdateWorldPos();

		glm::vec2 m_worldPos{};
		glm::vec2 m_localPos{};
		bool m_positionIsDirty{};

		//Components
		std::vector<std::shared_ptr<BaseComponent>> m_components;
		Transform m_transform{};
		std::shared_ptr<TransformComponent> m_pTransform{ nullptr };
		
		//parents-Children
		GameObject* m_parent{ nullptr };
		std::vector<GameObject*> m_children{};

		//Subject
		std::shared_ptr<Subject> m_Subject{ nullptr };
		std::vector<Observer*> m_Observers;

		//Gameobject tag
		Tag m_Tag{ Tag::Static }; //Standard static tag
	};

	template<typename T>
	std::shared_ptr <T> dae::GameObject::AddComponent()
	{
		std::shared_ptr component = std::make_shared<T>();
		static_assert((std::is_base_of<BaseComponent, T>::value) && ("Not inherited from basecomponent"));

		m_components.emplace_back(component);

		return component;
	}

	template<typename T>
	std::shared_ptr <T> dae::GameObject::GetComponent() const
	{
		for (auto& component : m_components)
		{
			std::shared_ptr<T> cast = std::dynamic_pointer_cast<T>(component);
			if(cast)
				return cast;
		}

		assert(!"Component not found in gameobject");
		return nullptr;
	}

	template<typename T>
	void dae::GameObject::RemoveComponent()
	{
		auto it{ m_components.begin() };
		for (it; it != m_components.end(); ++it)
		{
			if (dynamic_cast<T*>(it->get()))
			{
				m_components.erase(it);
				break;
			}
		}
	}
}
