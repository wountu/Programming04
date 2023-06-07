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
#include "Subject.h"
#include "HealthDisplayObserver.h"
#include "HealthComponent.h"
#include "ScoreDisplayObserver.h"
#include "ScoreComponent.h"
#include "BulletComponent.h"
#include "BulletManager.h"
#include "SoundEffectSystem.h"
#include "ServiceLocator.h"
#include "CollisionBoxComponent.h"
#include "AimComponent.h"

void load()
{
	std::cout << "how to play: \n";
	std::cout << "Tank 01 to move w a s d : \n";
	std::cout << "Tank 01 to shoot space (plays only sound for now) \n";
	std::cout << "Tank 02 to move use DPAD on XBOX \n";
	std::cout << "Tank 02 to shoot press v(plays only sound for now) \n";

	//Scene
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//Sound
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SoundEffectSystem>());

	auto backgroundGameObject = std::make_shared<dae::GameObject>();
	auto renderBackground = backgroundGameObject->AddComponent<dae::RenderComponent>();
	auto transformBackground = backgroundGameObject->AddComponent<dae::TransformComponent>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);

	std::shared_ptr<dae::Subject> subject = std::make_shared<dae::Subject>();

	auto backgroundTexture = dae::ResourceManager::GetInstance().LoadTexture("background.tga");
	renderBackground->Initialize(backgroundTexture, backgroundGameObject);
	transformBackground->Initialize(glm::vec2(0, 0), 0.f, backgroundGameObject);

	scene.Add(backgroundGameObject);



	auto daeTextureGameObject = std::make_shared<dae::GameObject>();
	auto renderCompDaeText = daeTextureGameObject->AddComponent<dae::RenderComponent>();
	auto transformCompDaeText = daeTextureGameObject->AddComponent<dae::TransformComponent>();

	auto texture = dae::ResourceManager::GetInstance().LoadTexture("logo.tga");
	renderCompDaeText->Initialize(texture, daeTextureGameObject);
	transformCompDaeText->Initialize(glm::vec2(216, 180), 0.f, daeTextureGameObject);

	scene.Add(daeTextureGameObject);


	auto fpsGameobject = std::make_shared<dae::GameObject>();
	auto transformComp = fpsGameobject->AddComponent<dae::TransformComponent>();
	auto textComp = fpsGameobject->AddComponent<dae::TextObject>();
	auto fps = fpsGameobject->AddComponent<dae::fpsCounter>();

	textComp->Initialize("Programming 4 Assignment", font, fpsGameobject);
	transformComp->Initialize(glm::vec2(5, 5), 0.f, fpsGameobject);
	fps->Initialize(fpsGameobject);

	scene.Add(fpsGameobject);


	const int startHealth{ 3 };
	const int startScore{ 0 };


	//TRONTANK01

	auto tronTank01 = std::make_shared <dae::GameObject>();
	auto healthTronTank01 = tronTank01->AddComponent<dae::HealthComponent>();
	auto scoreTronTank01 = tronTank01->AddComponent<dae::ScoreComponent>();
	auto renderCompTronTank01 = tronTank01->AddComponent<dae::RenderComponent>();
	auto transformTronTank01 = tronTank01->AddComponent <dae::TransformComponent>();

	auto tankCollision = tronTank01->AddComponent<dae::CollisionBoxComponent>();

	texture = dae::ResourceManager::GetInstance().LoadTexture("BlueTank.png");
	renderCompTronTank01->Initialize(texture, tronTank01);
	transformTronTank01->Initialize(glm::vec2(250, 400), 90.f, tronTank01);
	healthTronTank01->Initialize(startHealth, tronTank01);
	scoreTronTank01->Initialize(tronTank01);

	dae::CollisionBox box{};
	box._width = static_cast<float>(texture->GetSize().x);
	box._height = static_cast<float>(texture->GetSize().y);
	box._leftTop = transformTronTank01->GetLocalPosition();

	tankCollision->Initialize(tronTank01, box);

	tronTank01->SetSubject(subject);
	tronTank01->SetTag(dae::Player1);

	scene.Add(tronTank01);

	//Trontank aim
	auto aimTronTank01 = std::make_shared<dae::GameObject>(); 
	auto aimComponent = aimTronTank01->AddComponent<dae::AimComponent>();
	auto aimTransform = aimTronTank01->AddComponent<dae::TransformComponent>();
	auto bulletManager = aimTronTank01->AddComponent<dae::BulletManager>();
	auto renderCompAim = aimTronTank01->AddComponent<dae::RenderComponent>();

	aimTronTank01->Initialize();
	aimComponent->Initialize(aimTronTank01);
	aimTransform->Initialize(tronTank01->GetComponent<dae::TransformComponent>()->GetLocalPosition(), tronTank01->GetComponent<dae::TransformComponent>()->GetAngle(), aimTronTank01);
	bulletManager->Initialize(aimTronTank01);
	texture = dae::ResourceManager::GetInstance().LoadTexture("BlueTankGun.png");
	renderCompAim->Initialize(texture, aimTronTank01);

	aimTronTank01->SetParent(tronTank01, false);
	aimTronTank01->SetTag(dae::Player1);

	scene.Add(aimTronTank01);

	//Health observer for tron tank 01
	auto healthObserver_TT01 = std::make_shared <dae::GameObject>();

	auto textHealthObject_HO_TT01 = healthObserver_TT01->AddComponent <dae::TextObject>();
	auto textTransform_HO_TT01 = healthObserver_TT01->AddComponent<dae::TransformComponent>();

	textHealthObject_HO_TT01->Initialize((std::string("Health: " + std::to_string(startHealth))), font, healthObserver_TT01);
	textTransform_HO_TT01->Initialize(glm::vec2(5.f, 100.f), 0.f, healthObserver_TT01);
	
	healthObserver_TT01->Initialize();
	healthObserver_TT01->SetParent(tronTank01, true); //Needed for the observer

	//Adding the observers to the subject, and adding that subject to the gameobject
	dae::HealthDisplayObserver* healthDisplay_TT1 = new dae::HealthDisplayObserver(healthObserver_TT01, startHealth);
	subject->AddObserver(healthDisplay_TT1);
	healthObserver_TT01->SetSubject(subject);

	scene.Add(healthObserver_TT01);


	//Score observer for tron tank 02
	auto scoreObserver_TT01 = std::make_shared<dae::GameObject>();

	auto textScoreObject_SO_TT01 = scoreObserver_TT01->AddComponent<dae::TextObject>();
	auto textTransfrom_SO_TT1 = scoreObserver_TT01->AddComponent<dae::TransformComponent>();

	textScoreObject_SO_TT01->Initialize(std::string("Score: 0"), font, scoreObserver_TT01);
	textTransfrom_SO_TT1->Initialize(glm::vec2(5.f, 130.f), 0.f, scoreObserver_TT01);

	scoreObserver_TT01->Initialize();
	scoreObserver_TT01->SetParent(tronTank01, true);

	//Adding the observers to the subject, and adding that subject to the gameobject
	dae::ScoreDisplayObserver* scoreDisplay_TT1 = new dae::ScoreDisplayObserver(scoreObserver_TT01);
	subject->AddObserver(scoreDisplay_TT1);
	scoreObserver_TT01->SetSubject(subject);

	scene.Add(scoreObserver_TT01);



	//TRONTANK 2
	auto tronTank02 = std::make_shared <dae::GameObject>();

	auto renderCompTronTank02 = tronTank02->AddComponent<dae::RenderComponent>();
	auto transformTronTank02 = tronTank02->AddComponent <dae::TransformComponent>();

	auto healthTronTank02 = tronTank02->AddComponent<dae::HealthComponent>();
	//auto textScoreObjectTronTank02 = tronTank02->AddComponent<dae::TextObject>();
	auto scoreTronTank02 = tronTank02->AddComponent<dae::ScoreComponent>();
	//auto rotateCompTronTank02 = tronTank02->AddComponent<dae::RotateComponent>();
	//bulletManager = tronTank02->AddComponent<dae::BulletManager>();
	tankCollision = tronTank02->AddComponent<dae::CollisionBoxComponent>();

	tronTank02->Initialize();
	texture = dae::ResourceManager::GetInstance().LoadTexture("GreenTank.png");
	renderCompTronTank02->Initialize(texture, tronTank02);
	transformTronTank02->Initialize(glm::vec2(40, 0), 0.f, tronTank02);
	healthTronTank02->Initialize(startHealth, tronTank02);
	//textScoreObjectTronTank02->Initialize((std::string("Score: " + std::to_string(startScore))), font, tronTank02);
	scoreTronTank02->Initialize(tronTank02, startScore);
	//bulletManager->Initialize(tronTank02);

	box._width = static_cast<float>(texture->GetSize().x);
	box._height = static_cast<float>(texture->GetSize().y);
	box._leftTop = transformTronTank01->GetLocalPosition();

	tankCollision->Initialize(tronTank02, box);
	tronTank02->SetTag(dae::Player2);

	scene.Add(tronTank02);
	//rotateCompTronTank02->Initialize(tronTank02, 50.f);

	tronTank02->SetSubject(subject);


	//Health observer for tron tank 02
	auto healthObserver_TT02 = std::make_shared <dae::GameObject>();

	auto textHealthObject_HO_TT02 = healthObserver_TT02->AddComponent <dae::TextObject>();
	auto textTransform_HO_TT02 = healthObserver_TT02->AddComponent<dae::TransformComponent>();

	healthObserver_TT02->Initialize();
	textHealthObject_HO_TT02->Initialize((std::string("Health: " + std::to_string(startHealth))), font, healthObserver_TT02);
	textTransform_HO_TT02->Initialize(glm::vec2(5.f, 200.f), 0.f, healthObserver_TT02);

	healthObserver_TT02->SetParent(tronTank02, true); //Needed for the observer

	//Adding the observers to the subject, and adding that subject to the gameobject
	dae::HealthDisplayObserver* healthDisplay_TT2 = new dae::HealthDisplayObserver(healthObserver_TT02, startHealth);
	subject->AddObserver(healthDisplay_TT2);
	healthObserver_TT02->SetSubject(subject);

	scene.Add(healthObserver_TT02);

	//Score observer for tron tank 02
	auto scoreObserver_TT02 = std::make_shared<dae::GameObject>();

	auto textScoreObject_SO_TT02 = scoreObserver_TT02->AddComponent<dae::TextObject>();
	auto textTransfrom_SO_TT2 = scoreObserver_TT02->AddComponent<dae::TransformComponent>();

	scoreObserver_TT02->Initialize();
	textScoreObject_SO_TT02->Initialize(std::string("Score: 0"), font, scoreObserver_TT02);
	textTransfrom_SO_TT2->Initialize(glm::vec2(5.f, 230.f), 0.f, scoreObserver_TT02);

	//Adding the observers to the subject, and adding that subject to the gameobject
	dae::ScoreDisplayObserver* scoreDisplay_TT2 = new dae::ScoreDisplayObserver(scoreObserver_TT02);
	subject->AddObserver(scoreDisplay_TT2);
	scoreObserver_TT02->SetSubject(subject);

	scoreObserver_TT02->SetParent(tronTank02, true);

	scene.Add(scoreObserver_TT02);


	//Commands
	auto& input = dae::InputManager::GetInstance();
	unsigned controller = input.AddController();

	const float speed{ 50.f };
	auto pCommand = input.AddCommand<dae::Movement>(controller, tronTank01.get(), ControllerXbox::ControllerInputs::DPAD_UP, dae::InputManager::KeyPress::HOLD);
	pCommand->SetDirectionAndSpeed(glm::vec2{ 0.f, -1.f }, speed); // - in y is up 

	pCommand = input.AddCommand<dae::Movement>(controller, tronTank01.get(), ControllerXbox::ControllerInputs::DPAD_DOWN, dae::InputManager::KeyPress::HOLD);
	pCommand->SetDirectionAndSpeed(glm::vec2{ 0.f, 1.f }, speed);

	pCommand = input.AddCommand<dae::Movement>(controller, tronTank01.get(), ControllerXbox::ControllerInputs::DPAD_LEFT, dae::InputManager::KeyPress::HOLD);
	pCommand->SetDirectionAndSpeed(glm::vec2{ -1.f, 0.f }, speed);

	pCommand = input.AddCommand<dae::Movement>(controller, tronTank01.get(), ControllerXbox::ControllerInputs::DPAD_RIGHT, dae::InputManager::KeyPress::HOLD);
	pCommand->SetDirectionAndSpeed(glm::vec2{ 1.f, 0.f }, speed);

	pCommand = input.AddCommand<dae::Movement>(tronTank02.get(), SDL_SCANCODE_W, dae::InputManager::KeyPress::HOLD);
	pCommand->SetDirectionAndSpeed(glm::vec2{ 0.f, -1.f }, speed * 2.f);

	pCommand = input.AddCommand<dae::Movement>(tronTank02.get(), SDL_SCANCODE_S, dae::InputManager::KeyPress::HOLD);
	pCommand->SetDirectionAndSpeed(glm::vec2{ 0.f, 1.f }, speed * 2.f);

	pCommand = input.AddCommand<dae::Movement>(tronTank02.get(), SDL_SCANCODE_A, dae::InputManager::KeyPress::HOLD);
	pCommand->SetDirectionAndSpeed(glm::vec2{ -1.f, 0.f }, speed * 2.f);

	pCommand = input.AddCommand<dae::Movement>(tronTank02.get(), SDL_SCANCODE_D, dae::InputManager::KeyPress::HOLD);
	pCommand->SetDirectionAndSpeed(glm::vec2{ 1.f, 0.f }, speed * 2.f);

	//input.AddCommand <dae::Damage>(tronTank02.get(), SDL_SCANCODE_F, dae::InputManager::KeyPress::SINGLEPRESS);
	//input.AddCommand<dae::Damage>(controller, tronTank01.get(), ControllerXbox::ControllerInputs::A);

	input.AddCommand<dae::Shoot>(controller, tronTank01.get(), ControllerXbox::ControllerInputs::A, dae::InputManager::KeyPress::SINGLEPRESS);
	//input.AddCommand<dae::Shoot>(controller, tronTank01.get(), ControllerXbox::ControllerInputs::A);
	input.AddCommand<dae::Shoot>(tronTank02.get(), SDL_SCANCODE_SPACE, dae::InputManager::KeyPress::SINGLEPRESS);
	//input.AddCommand<dae::Shoot>(tronTank02.get(), SDL_SCANCODE_SPACE, dae::InputManager::KeyPress::SINGLEPRESS);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);

	return 0;
}