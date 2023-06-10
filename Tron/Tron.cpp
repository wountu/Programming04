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
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "BulletComponent.h"
#include "BulletManager.h"
#include "SoundEffectSystem.h"
#include "ServiceLocator.h"
#include "CollisionBoxComponent.h"
#include "AimComponent.h"
#include "LevelGenerator.h"
#include "HealthObserver.h"

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
	healthTronTank01->Initialize(startHealth, glm::vec2(80, 200), tronTank01);
	scoreTronTank01->Initialize(tronTank01);

	auto healthObserver = new dae::HealthObserver({ 500, 50 }, startHealth);
	healthTronTank01->AddObserver(healthObserver);

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


	////TRONTANK 2
	auto tronTank02 = std::make_shared <dae::GameObject>();

	auto renderCompTronTank02 = tronTank02->AddComponent<dae::RenderComponent>();
	auto transformTronTank02 = tronTank02->AddComponent <dae::TransformComponent>();
	auto healthTronTank02 = tronTank02->AddComponent<dae::HealthComponent>();
	tankCollision = tronTank02->AddComponent<dae::CollisionBoxComponent>();

	tronTank02->Initialize();
	texture = dae::ResourceManager::GetInstance().LoadTexture("GreenTank.png");
	renderCompTronTank02->Initialize(texture, tronTank02);
	transformTronTank02->Initialize(glm::vec2(40, 0), 0.f, tronTank02);
	healthTronTank02->Initialize(startHealth, glm::vec2(40, 0), tronTank02);

	auto healthObserver2 = new dae::HealthObserver({500, 100}, startHealth);
	healthTronTank02->AddObserver(healthObserver2);

	box._width = static_cast<float>(texture->GetSize().x);
	box._height = static_cast<float>(texture->GetSize().y);
	box._leftTop = transformTronTank01->GetLocalPosition();

	tankCollision->Initialize(tronTank02, box, 10);
	tronTank02->SetTag(dae::Player2);

	scene.Add(tronTank02);

	//Commands
	auto& input = dae::InputManager::GetInstance();
	unsigned controller = input.AddController();

	const float speed{ 100.f };
	auto pCommand = input.AddCommand<dae::Movement>(controller, tronTank02.get(), ControllerXbox::ControllerInputs::DPAD_UP, dae::InputManager::KeyPress::HOLD);
	pCommand->SetDirectionAndSpeed(glm::vec2{ 0.f, -1.f }, speed); // - in y is up 

	pCommand = input.AddCommand<dae::Movement>(controller, tronTank02.get(), ControllerXbox::ControllerInputs::DPAD_DOWN, dae::InputManager::KeyPress::HOLD);
	pCommand->SetDirectionAndSpeed(glm::vec2{ 0.f, 1.f }, speed);

	pCommand = input.AddCommand<dae::Movement>(controller, tronTank02.get(), ControllerXbox::ControllerInputs::DPAD_LEFT, dae::InputManager::KeyPress::HOLD);
	pCommand->SetDirectionAndSpeed(glm::vec2{ -1.f, 0.f }, speed);

	pCommand = input.AddCommand<dae::Movement>(controller, tronTank02.get(), ControllerXbox::ControllerInputs::DPAD_RIGHT, dae::InputManager::KeyPress::HOLD);
	pCommand->SetDirectionAndSpeed(glm::vec2{ 1.f, 0.f }, speed);

	pCommand = input.AddCommand<dae::Movement>(tronTank01.get(), SDL_SCANCODE_W, dae::InputManager::KeyPress::HOLD);
	pCommand->SetDirectionAndSpeed(glm::vec2{ 0.f, -1.f }, speed);

	pCommand = input.AddCommand<dae::Movement>(tronTank01.get(), SDL_SCANCODE_S, dae::InputManager::KeyPress::HOLD);
	pCommand->SetDirectionAndSpeed(glm::vec2{ 0.f, 1.f }, speed);

	pCommand = input.AddCommand<dae::Movement>(tronTank01.get(), SDL_SCANCODE_A, dae::InputManager::KeyPress::HOLD);
	pCommand->SetDirectionAndSpeed(glm::vec2{ -1.f, 0.f }, speed);

	pCommand = input.AddCommand<dae::Movement>(tronTank01.get(), SDL_SCANCODE_D, dae::InputManager::KeyPress::HOLD);
	pCommand->SetDirectionAndSpeed(glm::vec2{ 1.f, 0.f }, speed);

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