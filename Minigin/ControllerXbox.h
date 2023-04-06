#pragma once
class ControllerXbox
{
public:
	explicit ControllerXbox(int controllerIdx);
	virtual ~ControllerXbox();
	ControllerXbox(const ControllerXbox& other)				= delete;
	ControllerXbox& operator=(const ControllerXbox& other)  = delete;
	ControllerXbox(ControllerXbox&& other)					= delete;
	ControllerXbox& operator=(ControllerXbox&& other)		= delete;

	enum class ControllerInputs
	{
		DPAD_UP = 0x0001,
		DPAD_DOWN = 0x0002,
		DPAD_LEFT = 0x0004,
		DPAD_RIGHT = 0x0008,
		START = 0x0010,
		BACK = 0x0020,
		LEFT_THUMB = 0x0040,
		RIGHT_THUMB = 0x0080,
		LEFT_SHOULDER = 0x0100,
		RIGHT_SHOULDER = 0x0200,
		A = 0x1000,
		B = 0x2000,
		X = 0x4000,
		Y = 0x8000
	};
	void Update();

	bool IsDownThisFrame(ControllerInputs button) const;
	bool IsUpThisFrame(ControllerInputs button) const;
	bool IsPressed(ControllerInputs button) const;
private:
	class ControllerXboxImpl;
	ControllerXboxImpl* m_pImpl{ nullptr };
};

