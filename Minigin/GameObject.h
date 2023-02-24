#pragma once
#include <memory>
#include "Transform.h"

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:
		void Update();
		void Render() const;

		void SetTexture(const std::string& filename);
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
		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_texture{};
	};

	template<typename T>
	inline std::shared_ptr <T> dae::GameObject::AddComponent()
	{
		//std::shared_ptr <T> foundComponent = GetComponent<T>();
		//if (foundComponent)
		//{
		//	return foundComponent;
		//}


		//static_assert(std::is_base_of<Component, T>::value && "T must inherit from Compnent");

		//auto component = std::make_shared<T>();

		//component->SetOwner(shared_from_this());

		//m_Components.push_back(component);


		//return component;

		std::shared_ptr component = std::make_shared<T>();

		return component;
	}

}
