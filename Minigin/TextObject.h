#pragma once
#include <string>
#include <memory>
#include <SDL_ttf.h>

#include "GameObject.h"
#include "Transform.h"
#include "BaseComponent.h"
#include "TransformComponent.h"


namespace dae
{
	class Font;
	class Texture2D;
	class TextObject final : public BaseComponent
	{
	public:
		virtual void Initialize(const std::string& text, std::shared_ptr<Font> font, std::shared_ptr<GameObject> parent);
		virtual void Update() override;
		virtual void Render() const override;

		void SetText(const std::string& text);
		void SetFont(std::shared_ptr<Font> font);
		void SetColor(glm::vec3 color);
		void SetPos(glm::vec2 pos); //For if there is no transform comp

		std::string GetText() const;

		TextObject() = default;
		virtual ~TextObject() = default;
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;
	private:
		std::string m_text;
		std::shared_ptr<Font> m_font{ nullptr };
		std::shared_ptr<Texture2D> m_textTexture{ nullptr };
		std::shared_ptr<TransformComponent> m_transform{ nullptr };
		SDL_Color m_Color{};

		GameObject* m_Parent{ nullptr };
		glm::vec2 m_pos{};
	};
}
		