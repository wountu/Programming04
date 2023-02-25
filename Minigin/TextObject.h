#pragma once
#include <string>
#include <memory>

#include "GameObject.h"
#include "Transform.h"
#include "BaseComponent.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextObject final : public BaseComponent
	{
	public:
		virtual void Initialize(const std::string& text, std::shared_ptr<Font> font);
		virtual void Update() override;
		virtual void Render() const override;

		virtual void SetOwner(std::weak_ptr<GameObject> parent) override;

		void SetText(const std::string& text);
		//void SetPosition(float x, float y);
		void SetFont(std::shared_ptr<Font> font);

		TextObject(const std::string& text, std::shared_ptr<Font> font);
		TextObject() = default;
		virtual ~TextObject() = default;
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;
	private:
		std::string m_text;
		//Transform m_transform{};
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
	};
}
		