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
#include "SoundEffectSystem.h"
#include "ServiceLocator.h"
#include "CollisionBoxComponent.h"
#include "AimComponent.h"
#include "GridGenerator.h"
#include "HealthObserver.h"
#include "VisionComponent.h"
#include "AIComonent.h"
#include "ScoreObserver.h"
#include "Gamemode.h"
#include "LoadScenes.h"
#include "PacmanPrefab.h"
#include "DotsPrefab.h"
#include "MainPlayerPrefab.h"
#include "Command.h"
#include "MainmenuComponent.h"
#include "MainMenuObserver.h"
#include "CollectablesObserver.h"

void load()
{
	auto& sceneManager = dae::SceneManager::GetInstance();

	////Gamemode
	auto gameMode = std::make_shared<dae::Gamemode>();

	//Sound
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SoundEffectSystem>());

	//Main Menu
	static const auto mainMenu = sceneManager.CreateScene("Main menu");

	std::shared_ptr<dae::GameObject> menu = std::make_shared<dae::GameObject>();
	menu->Initialize();

	auto menuComponent = menu->AddComponent<dae::MainmenuComponent>();
	menuComponent->Initialize(menu, dae::Menu::SINGLE);
	
	auto menuObserver = std::make_shared<dae::MainMenuObserver>();
	menuObserver->Initialize(glm::vec2(220, 150), menuComponent->GetMenuText());
	menuComponent->AddObserver(menuObserver);
	menuComponent->AddObserver(gameMode);

	mainMenu->Add(menu);

	sceneManager.SetActiveScene(mainMenu);
	
	auto nextLevelCommand = dae::InputManager::GetInstance().AddCommand<dae::NextLevel>(nullptr, SDL_SCANCODE_F3, dae::InputManager::KeyPress::SINGLEPRESS);
	nextLevelCommand->SetGameMode(gameMode.get());

	dae::LevelLoader::GetInstance().LoadLevel("Level/level01.txt", gameMode, "Level01");
	dae::LevelLoader::GetInstance().LoadLevel("Level/level02.txt", gameMode, "Level02");
	dae::LevelLoader::GetInstance().LoadLevel("Level/level03.txt", gameMode, "Level03");
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);

	return 0;
}