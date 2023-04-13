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
#include "InputManager.h"
#include "ControllerXbox.h"
#include "Achievement.h"
#include "Subject.h"
#include "HealthDisplayObserver.h"
#include "HealthComponent.h"

void load()
{
	//Scene
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto backgroundGameObject = std::make_shared<dae::GameObject>();
	auto renderBackground = backgroundGameObject->AddComponent<dae::RenderComponent>();
	auto transformBackground = backgroundGameObject->AddComponent<dae::TransformComponent>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);

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
	auto transformComp = fpsGameobject->AddComponent<dae::TransformComponent>();
	auto textComp = fpsGameobject->AddComponent<dae::TextObject>();
	auto fps = fpsGameobject->AddComponent<dae::fpsCounter>();

	textComp->Initialize("Programming 4 Assignment", font, fpsGameobject);
	transformComp->Initialize(glm::vec2(5, 5), fpsGameobject);
	fps->Initialize(fpsGameobject);

	scene.Add(fpsGameobject);


	const int startHealth{ 3 };

	auto tronTank01 = std::make_shared <dae::GameObject>();
	auto textObjectTronTank01 = tronTank01->AddComponent <dae::TextObject>();
	auto healthTronTank01 = tronTank01->AddComponent<dae::HealthComponent>();
	auto renderCompTronTank01 = tronTank01->AddComponent<dae::RenderComponent>();
	auto transformTronTank01 = tronTank01->AddComponent <dae::TransformComponent>();

	texture = dae::ResourceManager::GetInstance().LoadTexture("tanks01.png");
	renderCompTronTank01->Initialize(texture, tronTank01);
	transformTronTank01->Initialize(glm::vec2(250, 400), tronTank01);
	textObjectTronTank01->Initialize((std::string("Health: " + std::to_string(startHealth))), font, tronTank01);
	healthTronTank01->Initialize(startHealth, tronTank01);

	std::shared_ptr<dae::Subject> subjectTank01 = std::make_shared<dae::Subject>();

	dae::HealthDisplayObserver* healthDisplayTank01 = new dae::HealthDisplayObserver(tronTank01, glm::vec2(20, 200));
	subjectTank01->AddObserver(healthDisplayTank01);
	tronTank01->SetSubject(subjectTank01);

	scene.Add(tronTank01);


	//TRONTANK 2
	auto tronTank02 = std::make_shared <dae::GameObject>();
	auto renderCompTronTank02 = tronTank02->AddComponent<dae::RenderComponent>();
	auto transformTronTank02 = tronTank02->AddComponent <dae::TransformComponent>();
	auto textObjectTronTank02 = tronTank02->AddComponent <dae::TextObject>();
	auto healthTronTank02 = tronTank02->AddComponent<dae::HealthComponent>();
	//auto rotateCompTronTank02 = tronTank02->AddComponent<dae::RotateComponent>();

	texture = dae::ResourceManager::GetInstance().LoadTexture("tanks01.png");
	renderCompTronTank02->Initialize(texture, tronTank02);
	transformTronTank02->Initialize(glm::vec2(40, 0), tronTank02);
	textObjectTronTank02->Initialize((std::string("Health: " + std::to_string(startHealth))), font, tronTank02);
	healthTronTank02->Initialize(startHealth, tronTank02);

	//rotateCompTronTank02->Initialize(tronTank02, 50.f);

	std::shared_ptr<dae::Subject> subject = std::make_shared<dae::Subject>();

	dae::HealthDisplayObserver* healthDisplay = new dae::HealthDisplayObserver(tronTank02, glm::vec2(20, 200));
	subject->AddObserver(healthDisplay);
	tronTank02->SetSubject(subject);

	scene.Add(tronTank02);

	//Commands
	auto& input = dae::InputManager::GetInstance();
	unsigned controller = input.AddController();

	const float speed{ 50.f };
	auto pCommand = input.AddCommand<dae::Movement>(controller, tronTank01.get(), ControllerXbox::ControllerInputs::DPAD_UP);
	pCommand->SetDirectionAndSpeed(glm::vec2{ 0.f, -1.f }, speed); // - in y is up 

	pCommand = input.AddCommand<dae::Movement>(controller, tronTank01.get(), ControllerXbox::ControllerInputs::DPAD_DOWN);
	pCommand->SetDirectionAndSpeed(glm::vec2{ 0.f, 1.f }, speed);

	pCommand = input.AddCommand<dae::Movement>(controller, tronTank01.get(), ControllerXbox::ControllerInputs::DPAD_LEFT);
	pCommand->SetDirectionAndSpeed(glm::vec2{ -1.f, 0.f }, speed);

	pCommand = input.AddCommand<dae::Movement>(controller, tronTank01.get(), ControllerXbox::ControllerInputs::DPAD_RIGHT);
	pCommand->SetDirectionAndSpeed(glm::vec2{ 1.f, 0.f }, speed);

	pCommand = input.AddCommand<dae::Movement>(tronTank02.get(), SDL_SCANCODE_W);
	pCommand->SetDirectionAndSpeed(glm::vec2{ 0.f, -1.f }, speed * 2.f);

	pCommand = input.AddCommand<dae::Movement>(tronTank02.get(), SDL_SCANCODE_S);
	pCommand->SetDirectionAndSpeed(glm::vec2{ 0.f, 1.f }, speed * 2.f);

	pCommand = input.AddCommand<dae::Movement>(tronTank02.get(), SDL_SCANCODE_A);
	pCommand->SetDirectionAndSpeed(glm::vec2{ -1.f, 0.f }, speed * 2.f);

	pCommand = input.AddCommand<dae::Movement>(tronTank02.get(), SDL_SCANCODE_D);
	pCommand->SetDirectionAndSpeed(glm::vec2{ 1.f, 0.f }, speed * 2.f);

	input.AddCommand <dae::Damage>(tronTank02.get(), SDL_SCANCODE_F);
	input.AddCommand<dae::Damage>(tronTank01.get(), SDL_SCANCODE_E);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	std::cout << "got here" << "\n";
    return 0;
}