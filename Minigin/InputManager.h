#pragma once
#include <map>

#include "Singleton.h"
#include "ControllerXbox.h"
#include "Command.h"
#include "SDL.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		enum class KeyPress
		{
			SINGLEPRESS,
			HOLD
		};

		virtual ~InputManager() = default;

		bool ProcessInput();
		unsigned AddController();
		template<typename T> T* AddCommand(unsigned controllerIdx, GameObject* pObject, ControllerXbox::ControllerInputs inputToPress, KeyPress keypress); //For xbox
		template<typename T> T* AddCommand(GameObject* pObject, SDL_Scancode key, KeyPress keypress); //For keyboard
		
		void RemoveCommand(Command* command);
	private:
		void AddInput();
		void DisableInput();

		using ControllerKey = std::pair<unsigned, ControllerXbox::ControllerInputs>;
		using ControllerCommandsMap = std::pair<ControllerKey, std::unique_ptr<Command>>;
		using ControllerCommandType = std::map<ControllerCommandsMap, KeyPress>;
		using KeyboardCommandsMap = std::map<SDL_Scancode, std::unique_ptr<Command>>;

		ControllerCommandsMap m_ConsoleCommands{};
		ControllerCommandType m_ConsoleCommandsType{};

		ControllerCommandType m_ConsoleCommandsTypeToAdd{};

		KeyboardCommandsMap m_HoldKeyboardCommands{};
		KeyboardCommandsMap m_PressKeyboardCommands{};

		KeyboardCommandsMap m_KeyboardCommandsToAdd{};

		std::vector<std::unique_ptr<ControllerXbox>> m_Controllers{};
		std::vector<SDL_Scancode> m_HoldKeys{};
		std::vector<SDL_Scancode> m_PressKeys{};

		std::vector< ControllerXbox::ControllerInputs> m_PressButtons{};

		std::vector<Command*> m_CommandsToDisable{};
	};


	template<typename T>
	inline T* InputManager::AddCommand(unsigned controllerIndex, GameObject* actor, ControllerXbox::ControllerInputs buttonToPress, KeyPress keypress)
	{
		for (size_t idx{}; idx < controllerIndex; ++idx)
		{
			AddController();
		}


		std::unique_ptr<T> command = std::make_unique<T>(actor);
		T* returnValue = command.get();

		m_ConsoleCommandsType.emplace( ControllerCommandsMap{ ControllerKey{controllerIndex, buttonToPress}, std::move(command)}, keypress);

		return returnValue;
	}

	template<typename T>
	inline T* InputManager::AddCommand(GameObject* actor, SDL_Scancode key, KeyPress keypress)
	{
		std::unique_ptr<T> command = std::make_unique<T>(actor);
		T* returnValue = command.get();

		if (keypress == KeyPress::HOLD)
			m_HoldKeyboardCommands[key] = std::move(command);
		else if (keypress == KeyPress::SINGLEPRESS)
			m_PressKeyboardCommands[key] = std::move(command);

		return returnValue;
	}

	//void InputManager::RemoveCommand(Command* command)
	//{

	//}

}
