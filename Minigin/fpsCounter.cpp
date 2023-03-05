#include <iostream>
#include "fpsCounter.h"
#include "TimeClass.h"
#include "Renderer.h"
#include "GameObject.h"


void dae::fpsCounter::Initialize(std::shared_ptr<GameObject> parent)
{
	m_Parent = parent;
	m_text = m_Parent->GetComponent<TextObject>();

	m_text->SetColor(glm::vec3(0, 255, 0));
}

void dae::fpsCounter::Update()
{
	auto& timeClass = TimeClass::GetInstance();

	int fps = timeClass.GetFps();

	m_text->SetText(std::to_string(fps) + " FPS");
}

void dae::fpsCounter::Render() const
{
}

int dae::fpsCounter::GetFps() const
{
	return m_fps;
}
