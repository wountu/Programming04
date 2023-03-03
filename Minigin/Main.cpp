#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <glm/vec2.hpp>

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "fpsCounter.h"
#include "Texture2D.h"
#include "RenderComponent.h"
#include "Renderer.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//auto go = std::make_shared<dae::GameObject>();
	//go->SetTexture("background.tga");
	//scene.Add(go);

	//go = std::make_shared<dae::GameObject>();
	//go->SetTexture("logo.tga");
	//go->SetPosition(216, 180);
	////go
	//scene.Add(go);

	auto backgroundGameObject = std::make_shared<dae::GameObject>();
	auto renderBackground = backgroundGameObject->AddComponent<dae::RenderComponent>();
	auto transformBackground = backgroundGameObject->AddComponent<dae::TransformComponent>();

	auto backgroundTexture = dae::ResourceManager::GetInstance().LoadTexture("background.tga");
	renderBackground->Initialize(backgroundTexture);
	transformBackground->Initialize(glm::vec2(0, 0));

	scene.Add(backgroundGameObject);



	auto daeTextureGameObject = std::make_shared<dae::GameObject>();
	auto renderCompDaeText = daeTextureGameObject->AddComponent<dae::RenderComponent>();
	auto transformCompDaeText = daeTextureGameObject->AddComponent<dae::TransformComponent>();

	auto texture = dae::ResourceManager::GetInstance().LoadTexture("logo.tga");
	renderCompDaeText->Initialize(texture);
	transformCompDaeText->Initialize(glm::vec2(216, 180));

	scene.Add(daeTextureGameObject);



	auto fpsGameobject = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto transformComp = fpsGameobject->AddComponent<dae::TransformComponent>();
	auto textComp = fpsGameobject->AddComponent<dae::TextObject>();
	auto fps = fpsGameobject->AddComponent<dae::fpsCounter>();

	textComp->Initialize("Programming 4 Assignment", font);
	transformComp->Initialize(glm::vec2(5, 5));
	fps->Initialize();

	scene.Add(fpsGameobject);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}