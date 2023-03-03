#include <iostream>
#include "fpsCounter.h"
#include "TimeClass.h"
#include "Renderer.h"
#include "GameObject.h"


void dae::fpsCounter::Initialize(std::shared_ptr<GameObject> parent)
{
	m_needsUpdate = true;
	m_Parent = parent;
	m_text = m_Parent->GetComponent<TextObject>();

	m_text->SetColor(glm::vec3(0, 255, 0));
}

void dae::fpsCounter::Update()
{
	auto& renderer = Renderer::GetInstance();
	auto& timeClass = TimeClass::GetInstance();

	renderer.Render();

	int fps = timeClass.GetFps();

	m_text->SetText(std::to_string(fps) + " FPS");
}

int dae::fpsCounter::GetFps() const
{
	return m_fps;
}
