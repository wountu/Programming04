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

		virtual bool GetNeedUpdate() const;
		virtual bool GetNeedRender() const;

	protected:
		bool m_needsUpdate{ false }; //If needed, overwrite in derived componentclasses
		bool m_needsRender{ false }; //Same as m_needsUpdate

		std::shared_ptr<GameObject> m_Parent;
	};

}
