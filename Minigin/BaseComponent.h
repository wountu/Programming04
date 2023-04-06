#pragma once
#include <memory>

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent() = default;
		virtual ~BaseComponent();

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent& operator=(const BaseComponent other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Initialize(std::shared_ptr<GameObject> parent);
		virtual void Update();
		virtual void Render() const;
	private:
		std::shared_ptr<GameObject> m_pParent{ nullptr };

	};

}

