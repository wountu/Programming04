#include <iostream>
#include "fpsCounter.h"
#include "TimeClass.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TextObject.h"

void dae::fpsCounter::Initialize()
{
	m_needsUpdate = true;
}

void dae::fpsCounter::Update()
{
	auto& renderer = Renderer::GetInstance();
	auto& timeClass = TimeClass::GetInstance();

	renderer.Render();

	int fps = timeClass.GetFps();

	auto text = m_Parent.lock()->GetComponent<TextObject>();
	text->SetText(std::to_string(fps));
}

void dae::fpsCounter::SetOwner(std::weak_ptr<GameObject> parent)
{
	m_Parent = parent;
}

int dae::fpsCounter::GetFps() const
{
	return m_fps;
}
