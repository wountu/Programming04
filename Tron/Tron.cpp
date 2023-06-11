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
#include "VisionComponent.h"
#include "AIComonent.h"
#include "ScoreObserver.h"
#include "Gamemode.h"

void load()
{
	std::cout << "how to play: \n";
	std::cout << "Tank 01 to move w a s d : \n";
	std::cout << "Tank 01 to shoot space (plays only sound for now) \n";
	std::cout << "Tank 02 to move use DPAD on XBOX \n";
	std::cout << "Tank 02 to shoot press v(plays only sound for now) \n";

	//Gamemode
	auto gameMode = dae::Gamemode::GameModeEnum::SINGLE_PLAYER;
	dae::Gamemode::GetInstance().SetGameMode(gameMode);

	//Scene
	const auto scene = dae::SceneManager::GetInstance().CreateScene("1st scene");
	const auto scene1 = dae::SceneManager::GetInstance().CreateScene("2nd scene");
	const auto scene2 = dae::SceneManager::GetInstance().CreateScene("3th scene");

	dae::SceneManager::GetInstance().SetActiveScene(scene);


	//Commands
	auto& input = dae::InputManager::GetInstance();


	//Levels

	auto pathWayTexture = dae::ResourceManager::GetInstance().LoadTexture("Level/Textures/path.png");
	auto wallTexture = dae::ResourceManager::GetInstance().LoadTexture("level/Textures/wall.png");
	auto voidTexture = dae::ResourceManager::GetInstance().LoadTexture("level/Textures/void.png");

	/// <summary>
	/// Level1
	/// </summary>
	auto& level = dae::LevelGenerator::GetInstance();
	level.LoadLevel("Level/LevelLayout0.csv");

	for (const auto& pathWay : level.GetPathWay())
	{
		auto block = std::make_shared<dae::GameObject>();
		auto render = block->AddComponent<dae::RenderComponent>();
		auto transform = block->AddComponent<dae::TransformComponent>();

		block->Initialize();
		transform->Initialize(pathWay.LeftTop, 0.f, block);
		render->Initialize(pathWayTexture, block);

		
		scene->Add(block);
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




		scene->Add(block);
	}

	for (const auto& activeVoid : level.GetVoid())
	{
		auto block = std::make_shared<dae::GameObject>();
		auto render = block->AddComponent<dae::RenderComponent>();
		auto transform = block->AddComponent<dae::TransformComponent>();

		block->Initialize();
		transform->Initialize(activeVoid.LeftTop, 0.f, block);
		render->Initialize(voidTexture, block);

		scene->Add(block);
	}

	/// <summary>
	/// Level2
	/// </summary>

	level.LoadLevel("Level/LevelLayout1.csv");

	for (const auto& pathWay : level.GetPathWay())
	{
		auto block = std::make_shared<dae::GameObject>();
		auto render = block->AddComponent<dae::RenderComponent>();
		auto transform = block->AddComponent<dae::TransformComponent>();

		block->Initialize();
		transform->Initialize(pathWay.LeftTop, 0.f, block);
		render->Initialize(pathWayTexture, block);


		scene1->Add(block);
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

		scene1->Add(block);
	}

	for (const auto& activeVoid : level.GetVoid())
	{
		auto block = std::make_shared<dae::GameObject>();
		auto render = block->AddComponent<dae::RenderComponent>();
		auto transform = block->AddComponent<dae::TransformComponent>();

		block->Initialize();
		transform->Initialize(activeVoid.LeftTop, 0.f, block);
		render->Initialize(voidTexture, block);

		scene1->Add(block);
	}

	/// <summary>
	/// Level 3
	/// </summary>
	/// 
	level.LoadLevel("Level/LevelLayout2.csv");

	for (const auto& pathWay : level.GetPathWay())
	{
		auto block = std::make_shared<dae::GameObject>();
		auto render = block->AddComponent<dae::RenderComponent>();
		auto transform = block->AddComponent<dae::TransformComponent>();

		block->Initialize();
		transform->Initialize(pathWay.LeftTop, 0.f, block);
		render->Initialize(pathWayTexture, block);


		scene2->Add(block);
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

		scene2->Add(block);
	}

	for (const auto& activeVoid : level.GetVoid())
	{
		auto block = std::make_shared<dae::GameObject>();
		auto render = block->AddComponent<dae::RenderComponent>();
		auto transform = block->AddComponent<dae::TransformComponent>();

		block->Initialize();
		transform->Initialize(activeVoid.LeftTop, 0.f, block);
		render->Initialize(voidTexture, block);

		scene2->Add(block);
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

	scene->Add(fpsGameobject);

	const int startHealth{ 3 };
	const float speed{ 100.f };

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

	auto scoreObserver = new dae::ScoreObserver({ 500, 65 }, 0);
	scoreTronTank01->AddObserver(scoreObserver);

	dae::CollisionBox box{};
	box._width = static_cast<float>(texture->GetSize().x);
	box._height = static_cast<float>(texture->GetSize().y);
	box._leftTop.x = transformTronTank01->GetLocalPosition().x;
	box._leftTop.y = transformTronTank01->GetLocalPosition().y;

	tankCollision->Initialize(tronTank01, box, 5);
	tronTank01->SetTag(dae::Player1);

	scene->Add(tronTank01);

	//Trontank aim
	auto aimTronTank01 = std::make_shared<dae::GameObject>(); 
	auto aimTransform = aimTronTank01->AddComponent<dae::TransformComponent>();
	auto bulletManager = aimTronTank01->AddComponent<dae::BulletManager>();
	auto renderCompAim = aimTronTank01->AddComponent<dae::RenderComponent>();

	aimTronTank01->Initialize();
	aimTransform->Initialize(glm::vec2{}, tronTank01->GetComponent<dae::TransformComponent>()->GetAngle(), aimTronTank01);
	bulletManager->Initialize(aimTronTank01);
	texture = dae::ResourceManager::GetInstance().LoadTexture("BlueTankGun.png");
	renderCompAim->Initialize(texture, aimTronTank01);

	aimTronTank01->SetParent(tronTank01, false);
	aimTronTank01->SetTag(dae::Player1);

	scene->Add(aimTronTank01);
	dae::Gamemode::GetInstance().AddPlayer(tronTank01);

	auto pCommand = input.AddCommand<dae::Movement>(tronTank01.get(), SDL_SCANCODE_W, dae::InputManager::KeyPress::HOLD);
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

	if (gameMode != dae::Gamemode::SINGLE_PLAYER)
	{
		unsigned controller = input.AddController();

		////TRONTANK 2
		auto tronTank02 = std::make_shared <dae::GameObject>();

		auto renderCompTronTank02 = tronTank02->AddComponent<dae::RenderComponent>();
		auto transformTronTank02 = tronTank02->AddComponent <dae::TransformComponent>();
		auto healthTronTank02 = tronTank02->AddComponent<dae::HealthComponent>();
		auto scoreTronTank02 = tronTank02->AddComponent<dae::ScoreComponent>();
		tankCollision = tronTank02->AddComponent<dae::CollisionBoxComponent>();

		tronTank02->Initialize();
		texture = dae::ResourceManager::GetInstance().LoadTexture("GreenTank.png");
		renderCompTronTank02->Initialize(texture, tronTank02);
		transformTronTank02->Initialize(glm::vec2(40, 0), 0.f, tronTank02);
		healthTronTank02->Initialize(startHealth, glm::vec2(40, 0), tronTank02);
		scoreTronTank02->Initialize(tronTank02);

		auto healthObserver2 = new dae::HealthObserver({ 500, 100 }, startHealth);
		healthTronTank02->AddObserver(healthObserver2);

		auto scoreObserver2 = new dae::ScoreObserver({ 500, 115 }, 0);
		scoreTronTank02->AddObserver(scoreObserver2);

		box._width = static_cast<float>(texture->GetSize().x);
		box._height = static_cast<float>(texture->GetSize().y);
		box._leftTop = transformTronTank01->GetLocalPosition();

		tankCollision->Initialize(tronTank02, box, 5);
		tronTank02->SetTag(dae::Player2);

		scene->Add(tronTank02);
		dae::Gamemode::GetInstance().AddPlayer(tronTank02);

		pCommand = input.AddCommand<dae::Movement>(controller, tronTank02.get(), ControllerXbox::ControllerInputs::DPAD_UP, dae::InputManager::KeyPress::HOLD);
		pCommand->SetDirectionAndSpeed(glm::vec2{ 0.f, -1.f }, speed); // - in y is up 

		pCommand = input.AddCommand<dae::Movement>(controller, tronTank02.get(), ControllerXbox::ControllerInputs::DPAD_DOWN, dae::InputManager::KeyPress::HOLD);
		pCommand->SetDirectionAndSpeed(glm::vec2{ 0.f, 1.f }, speed);

		pCommand = input.AddCommand<dae::Movement>(controller, tronTank02.get(), ControllerXbox::ControllerInputs::DPAD_LEFT, dae::InputManager::KeyPress::HOLD);
		pCommand->SetDirectionAndSpeed(glm::vec2{ -1.f, 0.f }, speed);

		pCommand = input.AddCommand<dae::Movement>(controller, tronTank02.get(), ControllerXbox::ControllerInputs::DPAD_RIGHT, dae::InputManager::KeyPress::HOLD);
		pCommand->SetDirectionAndSpeed(glm::vec2{ 1.f, 0.f }, speed);
	}

	if (gameMode != dae::Gamemode::VERSUS)
	{
		//AI
		const auto aiTexture = dae::ResourceManager::GetInstance().LoadTexture("GreenTank.png");

		auto aiTank01 = std::make_shared <dae::GameObject>();
		auto transformAITank01 = aiTank01->AddComponent <dae::TransformComponent>();
		auto renderCompAITank01 = aiTank01->AddComponent<dae::RenderComponent>();
		auto healthAITank01 = aiTank01->AddComponent<dae::HealthComponent>();
		auto AI1TankCollision = aiTank01->AddComponent<dae::CollisionBoxComponent>();
		auto visionAi1 = aiTank01->AddComponent<dae::VisionComponent>();

		aiTank01->Initialize();
		aiTank01->SetTag(dae::AI);
		transformAITank01->Initialize(glm::vec2(400, 390), 0.f, aiTank01);
		transformAITank01->SetDirection(glm::vec2{ -1, 0 });
		renderCompAITank01->Initialize(aiTexture, aiTank01);
		healthAITank01->Initialize(0, glm::vec2(400, 390), aiTank01);

		box._width = static_cast<float>(aiTexture->GetSize().x);
		box._height = static_cast<float>(aiTexture->GetSize().y);
		box._leftTop.x = transformTronTank01->GetLocalPosition().x;
		box._leftTop.y = transformTronTank01->GetLocalPosition().y;

		AI1TankCollision->Initialize(aiTank01, box, 5);
		visionAi1->Initialize(aiTank01, 500, { aiTexture->GetSize().x / 2, aiTexture->GetSize().y / 2 });


		//Aim
		auto aimAI01 = std::make_shared<dae::GameObject>();
		auto aimTransformAI01 = aimAI01->AddComponent<dae::TransformComponent>();
		auto renderCompAimAI01 = aimAI01->AddComponent<dae::RenderComponent>();
		auto bulletManagerAI01 = aimAI01->AddComponent<dae::BulletManager>();

		aimAI01->Initialize();
		aimAI01->SetParent(aiTank01, false);
		aimAI01->SetTag(dae::AI);
		aimTransformAI01->Initialize(glm::vec2{}, aiTank01->GetComponent<dae::TransformComponent>()->GetAngle(), aimAI01);
		texture = dae::ResourceManager::GetInstance().LoadTexture("GreenTankGun.png");
		renderCompAimAI01->Initialize(texture, aimAI01);
		bulletManagerAI01->Initialize(aimAI01);

		auto ai01 = aiTank01->AddComponent<dae::AIComponent>();
		ai01->Initialize(speed / 2.f, aiTank01, bulletManagerAI01);


		scene->Add(aimAI01);
		scene->Add(aiTank01);

		dae::Gamemode::GetInstance().AddEnemy(aiTank01);
	}


	//auto aiTank02 = std::make_shared <dae::GameObject>();
	//auto transformAITank02 = aiTank02->AddComponent <dae::TransformComponent>();
	//auto renderCompAITank02 = aiTank02->AddComponent<dae::RenderComponent>();
	//auto healthAITank02 = aiTank02->AddComponent<dae::HealthComponent>();
	//auto AI2TankCollision = aiTank02->AddComponent<dae::CollisionBoxComponent>();	
	//auto visionAi2 = aiTank02->AddComponent<dae::VisionComponent>();

	//aiTank02->Initialize();
	//aiTank02->SetTag(dae::AI);
	//transformAITank02->Initialize(glm::vec2(330, 60), 0.f, aiTank02);
	//transformAITank02->SetDirection(glm::vec2{ 0, 1 });	
	//renderCompAITank02->Initialize(aiTexture, aiTank02);
	//healthAITank02->Initialize(1, glm::vec2(320, 70), aiTank02);

	//box._width = static_cast<float>(aiTexture->GetSize().x);
	//box._height = static_cast<float>(aiTexture->GetSize().y);
	//box._leftTop.x = transformTronTank01->GetLocalPosition().x;
	//box._leftTop.y = transformTronTank01->GetLocalPosition().y;

	//AI2TankCollision->Initialize(aiTank02, box, 10);
	//visionAi2->Initialize(aiTank02, 500, { aiTexture->GetSize().x / 2, aiTexture->GetSize().y / 2 });

	//auto ai02 = aiTank02->AddComponent<dae::AIComponent>();
	//ai02->Initialize(speed / 2.f, aiTank02);


	//scene.Add(aiTank02);


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