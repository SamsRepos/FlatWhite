#pragma once

#include <SFML/Window/Event.hpp>

#include "common/Vec2f.hpp"
#include <vector>
#include <map>
#include <unordered_map>

namespace fw
{

const size_t KEYS_RANGE = 256;

enum class XboxButton : unsigned int
{
	A       = 0,
	B       = 1,
	X       = 2,
	Y       = 3,
	LB      = 4,
	RB      = 5,
	BACK    = 6,
	START   = 7,
	L_CLICK = 8,
	R_CLICK = 9
};
const unsigned int XBOX_BUTTONS_RANGE = 10;

enum class XboxTrigger
{
	LT,
	RT
};
const float XBOX_TRIGGER_PRESSED_THRESHOLD_DEFAULT = 70.f;

enum class XboxStick
{
	Left,
	Right,
	DPad
};

typedef sf::Keyboard Keyboard;

class Input
{
public:
	static bool eventIsInput(const sf::Event& event);
	void perFrameUpdate();
	void eventUpdate(const sf::Event& event);

	bool isKeyDown(int key) const;
	bool isKeyUp(int key) const;
	bool isKeyPressedNow(int key) const;
	bool isAnyKeyPressedNow(const std::vector<Keyboard::Key>& keys) const;
	bool isAnyKeyDown() const;
	bool isAnyKeyDown(const std::vector<Keyboard::Key>& keys) const;

	int getMousePosX() const;
	int getMousePosY() const;
	Vec2f getMousePosition() const;
	inline bool isMouseInWindow() const;

	bool isMouseLeftDown() const;
	bool isMouseRightDown() const;
	bool isMouseLeftClickedNow() const;
	bool isMouseRightClickedNow() const;

	bool isXboxControllerConnected() const;
	bool isXboxButtonDown(XboxButton button) const;
	bool isXboxButtonPressedNow(XboxButton button) const;
	bool isAnyXboxButtonPressedNow(const std::vector<XboxButton>& buttons) const;
	bool isAnyXboxButtonDown(const std::vector<XboxButton>& buttons) const;
	bool isXboxTriggerDown(XboxTrigger trigger, float threshold = XBOX_TRIGGER_PRESSED_THRESHOLD_DEFAULT) const;
	Vec2f getXboxStick(XboxStick stick) const;
	Vec2f getXboxStickIfExceededThresholdNow(XboxStick stick, float threshold) const;

private:
	void setKeyDown(int key);
	void setKeyUp(int key);
	void updateAnyKeyDown();

	void setMousePosX(int x);
	void setMousePosY(int y);
	void setMousePosition(int x, int y);
	void setMouseInWindow(bool in);

	void setMouseLeftDown(bool down);
	void setMouseRightDown(bool down);

	//void setMouseWheelDelta();

	bool m_keysDown[KEYS_RANGE]{ false };
	bool m_keysDownPreviously[KEYS_RANGE]{ false };
	bool m_anyKeyDown = false;

	bool m_xboxButtonsDown[XBOX_BUTTONS_RANGE]{ false };
	bool m_xboxButtonsDownPreviously[XBOX_BUTTONS_RANGE]{ false };

	std::map<XboxStick, fw::Vec2f> m_xBoxSticksPositions { 
		{ XboxStick::Left,  fw::Vec2f::zero() },
		{ XboxStick::Right, fw::Vec2f::zero() },
		{ XboxStick::DPad,  fw::Vec2f::zero() }
	};
	std::map<XboxStick, fw::Vec2f> m_xBoxSticksPositionsPreviously { 
		{ XboxStick::Left,  fw::Vec2f::zero() },
		{ XboxStick::Right, fw::Vec2f::zero() },
		{ XboxStick::DPad,  fw::Vec2f::zero() }
	};

	struct Mouse
	{
		int x = 0, y = 0;
		bool left = false, right = false;
		bool inWindow = false;
		int wheelDelta = 0;
	};
	Mouse m_mouse;
	Mouse m_previousMouse;
};

}