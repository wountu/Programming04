#pragma once
#include <memory>

#include "BaseComponent.h"
#include "TransformComponent.h"

namespace dae
{
	class Texture2D;
	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent() = default;
		virtual ~RenderComponent();
		RenderComponent(const RenderComponent& other)			 = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other)				 = delete;
		RenderComponent& operator=(RenderComponent&& other)		 = delete;

		virtual void Initialize(std::shared_ptr<Texture2D> texture, std::shared_ptr<GameObject> parent);
		virtual void Render() const override;

		void StopRendering(bool render);
	private:
		//std::shared_ptr<GameObject> m_pParent{ nullptr };
		std::shared_ptr<Texture2D> m_texture{ nullptr };
		std::shared_ptr<TransformComponent> m_transform{ nullptr };

		GameObject* m_Parent{ nullptr };

		bool m_Render{ true };
	};

}

