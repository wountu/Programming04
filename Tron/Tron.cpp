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
#include "LevelGenerator.h"

void load()
{
	std::cout << "how to play: \n";
	std::cout << "Tank 01 to move w a s d : \n";
	std::cout << "Tank 01 to shoot space (plays only sound for now) \n";
	std::cout << "Tank 02 to move use DPAD on XBOX \n";
	std::cout << "Tank 02 to shoot press v(plays only sound for now) \n";

	//Scene
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//Level
	auto& level = dae::LevelGenerator::GetInstance();
	level.LoadLevel("Level/LevelLayout0.csv");

	auto pathWayTexture = dae::ResourceManager::GetInstance().LoadTexture("Level/Textures/path.png");
	auto wallTexture = dae::ResourceManager::GetInstance().LoadTexture("level/Textures/wall.png");
	auto voidTexture = dae::ResourceManager::GetInstance().LoadTexture("level/Textures/void.png");

	for (const auto& pathWay : level.GetPathWay())
	{
		auto block = std::make_shared<dae::GameObject>();
		auto render = block->AddComponent<dae::RenderComponent>();
		auto transform = block->AddComponent<dae::TransformComponent>();

		block->Initialize();
		transform->Initialize(pathWay.LeftTop, 0.f, block);
		render->Initialize(pathWayTexture, block);


		scene.Add(block);
	}

	for (const auto& wall : level.GetWalls())
	{
		auto block = std::make_shared<dae::GameObject>();
		auto render = block->AddComponent<dae::RenderComponent>();
		auto transform = block->AddComponent<dae::TransformComponent>();
		auto collison = block->AddComponent<dae::CollisionBoxComponent>();

		dae::CollisionBox colBox;
		colBox._leftTop = wall.LeftTop;
		colBox._height = static_cast<float>(wall.Height);
		colBox._width = static_cast<float>(wall.Width);

		collison->Initialize(block, colBox, 0);
		block->Initialize();
		transform->Initialize(wall.LeftTop, 0.f, block);
		render->Initialize(wallTexture, block);




		scene.Add(block);
	}

	for (const auto& activeVoid : level.GetVoid())
	{
		auto block = std::make_shared<dae::GameObject>();
		auto render = block->AddComponent<dae::RenderComponent>();
		auto transform = block->AddComponent<dae::TransformComponent>();

		block->Initialize();
		transform->Initialize(activeVoid.LeftTop, 0.f, block);
		render->Initialize(voidTexture, block);

		scene.Add(block);
	}

	//Sound
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SoundEffectSystem>());

	auto fpsGameobject = std::make_shared<dae::GameObject>();
	auto transformComp = fpsGameobject->AddComponent<dae::TransformComponent>();
	auto textComp = fpsGameobject->AddComponent<dae::TextObject>();
	auto fps = fpsGameobject->AddComponent<dae::fpsCounter>();

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);

	textComp->Initialize("Programming 4 Assignment", font, fpsGameobject);
	transformComp->Initialize(glm::vec2(500, 5), 0.f, fpsGameobject);
	fps->Initialize(fpsGameobject);

	scene.Add(fpsGameobject);


	const int startHealth{ 3 };
	//const int startScore{ 0 };


	//TRONTANK01

	auto tronTank01 = std::make_shared <dae::GameObject>();
	auto healthTronTank01 = tronTank01->AddComponent<dae::HealthComponent>();
	auto scoreTronTank01 = tronTank01->AddComponent<dae::ScoreComponent>();
	auto renderCompTronTank01 = tronTank01->AddComponent<dae::RenderComponent>();
	auto transformTronTank01 = tronTank01->AddComponent <dae::TransformComponent>();

	auto tankCollision = tronTank01->AddComponent<dae::CollisionBoxComponent>();

	tronTank01->Initialize();
	auto texture = dae::ResourceManager::GetInstance().LoadTexture("BlueTank.png");
	renderCompTronTank01->Initialize(texture, tronTank01);
	transformTronTank01->Initialize(glm::vec2(80, 200), 180.f, tronTank01);
	healthTronTank01->Initialize(startHealth, tronTank01);
	scoreTronTank01->Initialize(tronTank01);

	dae::CollisionBox box{};
	box._width = static_cast<float>(texture->GetSize().x);
	box._height = static_cast<float>(texture->GetSize().y);
	box._leftTop.x = transformTronTank01->GetLocalPosition().x;
	box._leftTop.y = transformTronTank01->GetLocalPosition().y;

	tankCollision->Initialize(tronTank01, box, 10);
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
	aimTransform->Initialize(glm::vec2{}, tronTank01->GetComponent<dae::TransformComponent>()->GetAngle(), aimTronTank01);
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
	scene.Add(scoreObserver_TT01);



	////TRONTANK 2
	auto tronTank02 = std::make_shared <dae::GameObject>();

	auto renderCompTronTank02 = tronTank02->AddComponent<dae::RenderComponent>();
	auto transformTronTank02 = tronTank02->AddComponent <dae::TransformComponent>();
	auto healthTronTank02 = tronTank02->AddComponent<dae::HealthComponent>();
	//auto scoreTronTank02 = tronTank02->AddComponent<dae::ScoreComponent>();
	tankCollision = tronTank02->AddComponent<dae::CollisionBoxComponent>();

	tronTank02->Initialize();
	texture = dae::ResourceManager::GetInstance().LoadTexture("GreenTank.png");
	renderCompTronTank02->Initialize(texture, tronTank02);
	transformTronTank02->Initialize(glm::vec2(40, 0), 0.f, tronTank02);
	healthTronTank02->Initialize(startHealth, tronTank02);
	//scoreTronTank02->Initialize(tronTank02, startScore);

	box._width = static_cast<float>(texture->GetSize().x);
	box._height = static_cast<float>(texture->GetSize().y);
	box._leftTop = transformTronTank01->GetLocalPosition();

	tankCollision->Initialize(tronTank02, box, 5);
	tronTank02->SetTag(dae::Player2);

	scene.Add(tronTank02);
	//rotateCompTronTank02->Initialize(tronTank02, 50.f);


	//Health observer for tron tank 02
	auto healthObserver_TT02 = std::make_shared <dae::GameObject>();

	auto textHealthObject_HO_TT02 = healthObserver_TT02->AddComponent <dae::TextObject>();
	auto textTransform_HO_TT02 = healthObserver_TT02->AddComponent<dae::TransformComponent>();

	healthObserver_TT02->Initialize();
	textHealthObject_HO_TT02->Initialize((std::string("Health: " + std::to_string(startHealth))), font, healthObserver_TT02);
	textTransform_HO_TT02->Initialize(glm::vec2(5.f, 200.f), 0.f, healthObserver_TT02);

	healthObserver_TT02->SetParent(tronTank02, true); //Needed for the observer

	//Adding the observers to the subject, and adding that subject to the gameobject

	scene.Add(healthObserver_TT02);

	//Score observer for tron tank 02
	auto scoreObserver_TT02 = std::make_shared<dae::GameObject>();

	auto textScoreObject_SO_TT02 = scoreObserver_TT02->AddComponent<dae::TextObject>();
	auto textTransfrom_SO_TT2 = scoreObserver_TT02->AddComponent<dae::TransformComponent>();

	scoreObserver_TT02->Initialize();
	textScoreObject_SO_TT02->Initialize(std::string("Score: 0"), font, scoreObserver_TT02);
	textTransfrom_SO_TT2->Initialize(glm::vec2(5.f, 230.f), 0.f, scoreObserver_TT02);

	//Adding the observers to the subject, and adding that subject to the gameobject
	scoreObserver_TT02->SetParent(tronTank02, true);

	scene.Add(scoreObserver_TT02);


	//Commands
	auto& input = dae::InputManager::GetInstance();
	//unsigned controller = input.AddController();

	const float speed{ 50.f };
	//auto pCommand = input.AddCommand<dae::Movement>(controller, tronTank02.get(), ControllerXbox::ControllerInputs::DPAD_UP, dae::InputManager::KeyPress::HOLD);
	//pCommand->SetDirectionAndSpeed(glm::vec2{ 0.f, -1.f }, speed); // - in y is up 

	//pCommand = input.AddCommand<dae::Movement>(controller, tronTank02.get(), ControllerXbox::ControllerInputs::DPAD_DOWN, dae::InputManager::KeyPress::HOLD);
	//pCommand->SetDirectionAndSpeed(glm::vec2{ 0.f, 1.f }, speed);

	//pCommand = input.AddCommand<dae::Movement>(controller, tronTank02.get(), ControllerXbox::ControllerInputs::DPAD_LEFT, dae::InputManager::KeyPress::HOLD);
	//pCommand->SetDirectionAndSpeed(glm::vec2{ -1.f, 0.f }, speed);

	//pCommand = input.AddCommand<dae::Movement>(controller, tronTank02.get(), ControllerXbox::ControllerInputs::DPAD_RIGHT, dae::InputManager::KeyPress::HOLD);
	//pCommand->SetDirectionAndSpeed(glm::vec2{ 1.f, 0.f }, speed);

	auto pCommand = input.AddCommand<dae::Movement>(tronTank01.get(), SDL_SCANCODE_W, dae::InputManager::KeyPress::HOLD);
	pCommand->SetDirectionAndSpeed(glm::vec2{ 0.f, -1.f }, speed * 2.f);

	pCommand = input.AddCommand<dae::Movement>(tronTank01.get(), SDL_SCANCODE_S, dae::InputManager::KeyPress::HOLD);
	pCommand->SetDirectionAndSpeed(glm::vec2{ 0.f, 1.f }, speed * 2.f);

	pCommand = input.AddCommand<dae::Movement>(tronTank01.get(), SDL_SCANCODE_A, dae::InputManager::KeyPress::HOLD);
	pCommand->SetDirectionAndSpeed(glm::vec2{ -1.f, 0.f }, speed * 2.f);

	pCommand = input.AddCommand<dae::Movement>(tronTank01.get(), SDL_SCANCODE_D, dae::InputManager::KeyPress::HOLD);
	pCommand->SetDirectionAndSpeed(glm::vec2{ 1.f, 0.f }, speed * 2.f);

	auto pShoot = input.AddCommand<dae::Shoot>(aimTronTank01.get(), SDL_SCANCODE_LEFT, dae::InputManager::KeyPress::SINGLEPRESS);
	pShoot->SetDirection(glm::vec2{ -1,0 });

	pShoot = input.AddCommand<dae::Shoot>(aimTronTank01.get(), SDL_SCANCODE_RIGHT, dae::InputManager::KeyPress::SINGLEPRESS);
	pShoot->SetDirection(glm::vec2{ 1,0 });

	pShoot = input.AddCommand<dae::Shoot>(aimTronTank01.get(), SDL_SCANCODE_UP, dae::InputManager::KeyPress::SINGLEPRESS);
	pShoot->SetDirection(glm::vec2{ 0,-1 });

	pShoot = input.AddCommand<dae::Shoot>(aimTronTank01.get(), SDL_SCANCODE_DOWN, dae::InputManager::KeyPress::SINGLEPRESS);
	pShoot->SetDirection(glm::vec2{ 0,1 });


	//input.AddCommand <dae::Damage>(tronTank02.get(), SDL_SCANCODE_F, dae::InputManager::KeyPress::SINGLEPRESS);
	//input.AddCommand<dae::Damage>(controller, tronTank01.get(), ControllerXbox::ControllerInputs::A);

	//input.AddCommand<dae::Shoot>(controller, tronTank01.get(), ControllerXbox::ControllerInputs::A, dae::InputManager::KeyPress::SINGLEPRESS);
	//input.AddCommand<dae::Shoot>(controller, tronTank01.get(), ControllerXbox::ControllerInputs::A);
	//input.AddCommand<dae::Shoot>(tronTank02.get(), SDL_SCANCODE_SPACE, dae::InputManager::KeyPress::SINGLEPRESS);
	//input.AddCommand<dae::Shoot>(tronTank02.get(), SDL_SCANCODE_SPACE, dae::InputManager::KeyPress::SINGLEPRESS);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);

	return 0;
}