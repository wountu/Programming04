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
#include "RotateComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto backgroundGameObject = std::make_shared<dae::GameObject>();
	auto renderBackground = backgroundGameObject->AddComponent<dae::RenderComponent>();
	auto transformBackground = backgroundGameObject->AddComponent<dae::TransformComponent>();

	auto backgroundTexture = dae::ResourceManager::GetInstance().LoadTexture("background.tga");
	renderBackground->Initialize(backgroundTexture, backgroundGameObject);
	transformBackground->Initialize(glm::vec2(0, 0), backgroundGameObject);

	scene.Add(backgroundGameObject);



	auto daeTextureGameObject = std::make_shared<dae::GameObject>();
	auto renderCompDaeText = daeTextureGameObject->AddComponent<dae::RenderComponent>();
	auto transformCompDaeText = daeTextureGameObject->AddComponent<dae::TransformComponent>();

	auto texture = dae::ResourceManager::GetInstance().LoadTexture("logo.tga");
	renderCompDaeText->Initialize(texture, daeTextureGameObject);
	transformCompDaeText->Initialize(glm::vec2(216, 180), daeTextureGameObject);

	scene.Add(daeTextureGameObject);



	auto fpsGameobject = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto transformComp = fpsGameobject->AddComponent<dae::TransformComponent>();
	auto textComp = fpsGameobject->AddComponent<dae::TextObject>();
	auto fps = fpsGameobject->AddComponent<dae::fpsCounter>();

	textComp->Initialize("Programming 4 Assignment", font, fpsGameobject);
	transformComp->Initialize(glm::vec2(5, 5), fpsGameobject);
	fps->Initialize(fpsGameobject);

	scene.Add(fpsGameobject);



	auto tronTank01 = std::make_shared <dae::GameObject>();
	auto renderCompTronTank01 = tronTank01->AddComponent<dae::RenderComponent>();
	auto transformTronTank01 = tronTank01->AddComponent <dae::TransformComponent>();

	texture = dae::ResourceManager::GetInstance().LoadTexture("tanks01.png");
	renderCompTronTank01->Initialize(texture, tronTank01);
	transformTronTank01->Initialize(glm::vec2(250, 400), tronTank01);

	scene.Add(tronTank01);



	auto tronTank02 = std::make_shared <dae::GameObject>();
	auto renderCompTronTank02 = tronTank02->AddComponent<dae::RenderComponent>();
	auto transformTronTank02 = tronTank02->AddComponent <dae::TransformComponent>();
	auto rotateCompTronTank02 = tronTank02->AddComponent<dae::RotateComponent>();

	texture = dae::ResourceManager::GetInstance().LoadTexture("tanks01.png");
	renderCompTronTank02->Initialize(texture, tronTank02);
	transformTronTank02->Initialize(glm::vec2(40, 0), tronTank02);
	rotateCompTronTank02->Initialize(tronTank02, 50.f);

	tronTank02->SetParent(tronTank01, true);

	scene.Add(tronTank02);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}