#pragma once
#include <map>

#include "Singleton.h"
#include "ControllerXbox.h"
#include "Command.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		unsigned AddController();
		template<typename T> T* AddCommand(unsigned controllerIdx, GameObject* pObject, ControllerXbox::ControllerInputs inputToPress); //For xbox
		template<typename T> T* AddCommand(GameObject* pObject, SDL_Scancode key); //For keyboard
	private:
		using ControllerKey = std::pair<unsigned, ControllerXbox::ControllerInputs>;
		using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<Command>>;
		using KeyboardCommandsMap = std::map<SDL_Scancode, std::unique_ptr<Command>>;
		ControllerCommandsMap m_ConsoleCommands{};
		KeyboardCommandsMap m_KeyboardCommands{};
		std::vector<std::unique_ptr<ControllerXbox>> m_Controllers;

		std::vector<SDL_Scancode> m_PressedKeys{};
	};


	template<typename T>
	inline T* InputManager::AddCommand(unsigned controllerIndex, GameObject* actor, ControllerXbox::ControllerInputs buttonToPress)
	{
		for (size_t idx{}; idx < controllerIndex; ++idx)
		{
			AddController();
		}


		std::unique_ptr<T> command = std::make_unique<T>(actor);
		T* returnValue = command.get();
		ControllerKey keyToPress = std::make_pair(controllerIndex, buttonToPress);

		m_ConsoleCommands.insert({ keyToPress , std::move(command) });

		return returnValue;
	}

	template<typename T>
	inline T* InputManager::AddCommand(GameObject* actor, SDL_Scancode key)
	{
		std::unique_ptr<T> command = std::make_unique<T>(actor);
		T* returnValue = command.get();

		m_KeyboardCommands.insert({ key , std::move(command) });

		return returnValue;
	}
}
