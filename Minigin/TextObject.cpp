#include <stdexcept>
#include <iostream>
#include <memory>

#include "TextObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

void dae::TextObject::Initialize(const std::string& text, std::shared_ptr<Font> font, std::shared_ptr<GameObject> parent)
{
	m_text = text;
	m_font = std::move(font);
	m_textTexture = nullptr;
	m_Parent = parent;
	const SDL_Color white = { 255, 255, 255 };
	m_Color = white;

	m_transform = m_Parent->GetComponent<TransformComponent>();
}

void dae::TextObject::Update()
{
	const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_Color);
	if (surf == nullptr) 
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr) 
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_textTexture = std::make_shared<Texture2D>(texture);
}

void dae::TextObject::Render() const
{
	auto& renderer = Renderer::GetInstance();

	if (m_textTexture != nullptr)
	{
		renderer.SetRenderPos(m_transform->GetPosition());
		renderer.RenderTexture(*m_textTexture);
	}
}


// This implementation uses the "dirty flag" pattern
void dae::TextObject::SetText(const std::string& text)
{
	m_text = text;
}

//void dae::TextObject::SetPosition(const float x, const float y)
//{
//	//m_transform.SetPosition(x, y, 0.0f);
//}

void dae::TextObject::SetFont(std::shared_ptr<Font> font)
{

}

void dae::TextObject::SetColor(glm::vec3 color)
{
	m_Color.r = static_cast<Uint8>(color.x);
	m_Color.g = static_cast<Uint8>(color.y);
	m_Color.b = static_cast<Uint8>(color.z);
}
