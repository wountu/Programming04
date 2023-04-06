#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#pragma comment(lib, "xinput.lib")

#include "ControllerXbox.h"

class ControllerXbox::ControllerXboxImpl final
{
public:
	ControllerXboxImpl(unsigned int controllerIdx)
	{
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		m_ControllerIdx = controllerIdx;
	}

	virtual ~ControllerXboxImpl() = default;

	ControllerXboxImpl(const ControllerXboxImpl& other) = delete;
	ControllerXboxImpl(ControllerXboxImpl&& other) = delete;
	ControllerXboxImpl& operator=(const ControllerXboxImpl& other) = delete;
	ControllerXboxImpl& operator=(ControllerXboxImpl&& other) = delete;



	void Update()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIdx, &m_CurrentState);

		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		buttonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		buttonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}

	bool IsDownThisFrame(unsigned int button) const { return buttonsPressedThisFrame & button; }
	bool IsUpThisFrame(unsigned int button) const { return buttonsReleasedThisFrame & button;  }
	bool IsPressed(unsigned int button) const { return m_CurrentState.Gamepad.wButtons & button; }
private:
	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};

	WORD buttonsPressedThisFrame;
	WORD buttonsReleasedThisFrame;

	unsigned int m_ControllerIdx;
};

ControllerXbox::ControllerXbox(int controllerIdx)
{
	m_pImpl = new ControllerXboxImpl(controllerIdx);
}

ControllerXbox::~ControllerXbox()
{
	delete m_pImpl;
	m_pImpl = nullptr;
}

void ControllerXbox::Update()
{
	m_pImpl->Update();
}

bool ControllerXbox::IsDownThisFrame(ControllerInputs button) const
{
	return m_pImpl->IsDownThisFrame(static_cast<unsigned int> (button));
}

bool ControllerXbox::IsUpThisFrame(ControllerInputs button) const
{
	return m_pImpl->IsUpThisFrame(static_cast<unsigned int>(button));
}

bool ControllerXbox::IsPressed(ControllerInputs button) const
{
	return m_pImpl->IsPressed(static_cast<unsigned int>(button));
}