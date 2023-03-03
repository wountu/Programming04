#pragma once
#include <memory>

#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent() = default;
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other)			 = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other)				 = delete;
		RenderComponent& operator=(RenderComponent&& other)		 = delete;

		virtual void Initialize(std::shared_ptr<Texture2D> texture);
		virtual void Render() const override;

		virtual void SetParent(std::weak_ptr<GameObject> parent) override;
	private:
		std::shared_ptr<Texture2D> m_texture{ nullptr };
	};

}

