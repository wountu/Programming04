#pragma once
#include <memory>
#include <vector>
#include <iostream>
#include <string_view>

#include "TransformComponent.h"
#include "Transform.h"
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	//class BaseComponent;

	// todo: this should become final.
	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		void Update();
		void Render() const;

		//void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);	

		template <typename T> std::shared_ptr <T> AddComponent();
		template <typename T> std::shared_ptr <T> GetComponent() const;
		template <typename T> void RemoveComponent();


		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<std::shared_ptr<BaseComponent>> m_components;
		Transform m_transform{};
		std::shared_ptr<TransformComponent> m_pTransform{ nullptr };
		// todo: mmm, every gameobject has a texture? Is that correct?
		//std::shared_ptr<Texture2D> m_texture{};
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
