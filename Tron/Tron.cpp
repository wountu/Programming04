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
#include "LoadScenes.h"

void load()
{
	std::cout << "how to play: \n";
	std::cout << "Tank 01 to move w a s d : \n";
	std::cout << "Tank 01 to shoot space (plays only sound for now) \n";
	std::cout << "Tank 02 to move use DPAD on XBOX \n";
	std::cout << "Tank 02 to shoot press v(plays only sound for now) \n";

	auto& sceneManager = dae::SceneManager::GetInstance();

	//Gamemode
	auto gameMode = dae::Gamemode::GameModeEnum::SINGLE_PLAYER;
	dae::Gamemode::GetInstance().SetGameMode(gameMode);

	//Sound
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SoundEffectSystem>());

	//Main Menu
	static const auto mainMenu = sceneManager.CreateScene("Main menu");

	//Gamemode text
	std::shared_ptr<dae::GameObject> gameModeText = std::make_shared<dae::GameObject>();
	gameModeText->Initialize();

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto text = gameModeText->AddComponent<dae::TextObject>();
	text->Initialize("Gamemode: ", font, gameModeText);
	text->SetPos({ 200, 100 });

	mainMenu->Add(gameModeText);

	//Gamemode picker
	std::shared_ptr<dae::GameObject> gamemodePicker = std::make_shared<dae::GameObject>();
	gamemodePicker->Initialize();

	text = gamemodePicker->AddComponent<dae::TextObject>();
	text->Initialize("Single player", font, gamemodePicker);
	text->SetPos({ 200, 200 });

	dae::InputManager::GetInstance().AddCommand<dae::NextGamemode>(gamemodePicker.get(), SDL_SCANCODE_E, dae::InputManager::KeyPress::SINGLEPRESS);
	dae::InputManager::GetInstance().AddCommand <dae::Start>(gamemodePicker.get(), SDL_SCANCODE_SPACE, dae::InputManager::KeyPress::SINGLEPRESS);

	mainMenu->Add(gamemodePicker);

	sceneManager.SetActiveScene(mainMenu);

	std::unique_ptr<dae::LevelData> pLevel = dae::LevelGenerator::GetInstance().LoadLevel("Level/LevelLayout2.csv");
	auto scene = sceneManager.CreateScene("1st Scene");

	auto& resourceMan = dae::ResourceManager::GetInstance();
	auto& gridGen = dae::GridGenerator::GetInstance();

	auto pathTexture = resourceMan.LoadTexture("path.png");
	auto wallTexture = resourceMan.LoadTexture("wall.png");
	auto dotTexture = resourceMan.LoadTexture("pill.png");

	gridGen.LinkTextureToTile(dae::TileType::PATH, pathTexture);
	gridGen.LinkTextureToTile(dae::TileType::WALL, wallTexture);

	auto grid = gridGen.CreateGrid("Level/level.txt", glm::vec2(pathTexture->GetSize().x, pathTexture->GetSize().y));
	scene->Add(gridGen.CreateGameObjects(grid));

	for (const auto& tile : grid)
	{
		if (tile.hasDot)
		{
			auto dot = std::make_shared<dae::GameObject>();
			dot->Initialize();
			dot->SetTag(dae::Dot);

			auto transform = dot->AddComponent<dae::TransformComponent>();
			transform->Initialize(tile.LeftTop, 0.f, dot);

			auto render = dot->AddComponent<dae::RenderComponent>();
			render->Initialize(dotTexture, dot);

			scene->Add(dot);
		}
	}
	
	//dae::LevelGenerator::GetInstance().("Level/level.json");


	//Commands
    //auto& input = dae::InputManager::GetInstance();


	//Levels



	/// <summary>
	/// Level1
	/// </summary>


	/// <summary>
	/// Level2
	/// </summary>

	

	///// <summary>
	///// Level 3
	///// </summary>
	///// 
	



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