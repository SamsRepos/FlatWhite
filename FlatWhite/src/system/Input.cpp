#include "system/Input.h"

#include <iostream>

namespace fw
{

const float XBOX_AXIS_MIN_THRESHOLD = 10.f;

//
//  PUBLIC UPDATES:
//

bool Input::eventIsInput(const sf::Event& event)
{
	if (event.type == sf::Event::Closed)
		switch (event.type) {
		case sf::Event::KeyPressed:
		case sf::Event::KeyReleased:
		case sf::Event::MouseMoved:
		case sf::Event::MouseButtonPressed:
		case sf::Event::MouseButtonReleased:
		case sf::Event::MouseEntered:
		case sf::Event::MouseLeft:
			//case sf::Event::MouseWheelScrolled:
			return true;
		default:
			return false;
		}
}

void Input::perFrameUpdate()
{
	std::copy(std::begin(m_keysDown), std::end(m_keysDown), std::begin(m_keysDownPreviously));
	m_previousMouse = m_mouse;

	if (sf::Joystick::isConnected(0))
	{
		std::copy(std::begin(m_xboxButtonsDown), std::end(m_xboxButtonsDown), std::begin(m_xboxButtonsDownPreviously));

		sf::Joystick::update();
		for (auto i = 0; i < XBOX_BUTTONS_RANGE; ++i)
		{
			m_xboxButtonsDown[i] = sf::Joystick::isButtonPressed(0, unsigned int(i));
		}
	}
	
}

void Input::eventUpdate(const sf::Event& event)
{
	switch (event.type) {
	case sf::Event::KeyPressed:
		setKeyDown(event.key.code);
		updateAnyKeyDown();
		break;
	case sf::Event::KeyReleased:
		setKeyUp(event.key.code);
		updateAnyKeyDown();
		break;
	case sf::Event::MouseMoved:
		setMousePosition(event.mouseMove.x,
			event.mouseMove.y);
		break;
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			setMouseLeftDown(true);
		}
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			setMouseRightDown(true);
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			setMouseLeftDown(false);
		}
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			setMouseRightDown(false);
		}
		break;
	case sf::Event::MouseEntered:
		setMouseInWindow(true);
		break;
	case sf::Event::MouseLeft:
		setMouseInWindow(false);
		break;
		//case sf::Event::MouseWheelScrolled:
		//	event.mouseWheel.delta // pos up, neg down
		//	break;
	}

	//debugOut();
}

//
//  PUBLIC GETTERS:
//

// returns true if out of range
bool rangeCheck(int key, int range)
{
	return key < 0 || key >= range;
}

bool Input::isKeyDown(int key) const
{
	if (rangeCheck(key, KEYS_RANGE)) return false;

	return m_keysDown[key];
}

bool Input::isKeyUp(int key) const
{
	if (rangeCheck(key, KEYS_RANGE)) return false;

	return !(m_keysDown[key]);
}

bool Input::isKeyPressedNow(int key) const
{
	if (rangeCheck(key, KEYS_RANGE)) return false;

	bool isKeyDownNow = isKeyDown(key);
	bool wasKeyUpBefore = !(m_keysDownPreviously[key]);

	bool res = isKeyDownNow && wasKeyUpBefore;

	return res;
}

bool Input::isAnyKeyDown() const
{
	return m_anyKeyDown;
}

int Input::getMousePosX() const
{
	return m_mouse.x;
}

int Input::getMousePosY() const
{
	return m_mouse.y;
}

Vec2f Input::getMousePosition() const
{
	return Vec2f(m_mouse.x, m_mouse.y);
}

bool Input::isMouseInWindow() const
{
	return m_mouse.inWindow;
}

bool Input::isMouseLeftDown() const
{
	return m_mouse.left;
}

bool Input::isMouseRightDown() const
{
	return m_mouse.right;
}

bool Input::isMouseLeftClickedNow() const
{
	return m_mouse.left && !m_previousMouse.left;
}

bool Input::isMouseRightClickedNow() const
{
	return m_mouse.right && !m_previousMouse.right;
}

bool Input::isXboxControllerConnected() const
{
	return sf::Joystick::isConnected(0);
}

bool Input::isXboxButtonDown(XboxButton button) const
{
	if (rangeCheck(unsigned int(button), XBOX_BUTTONS_RANGE)) return false;

	return m_xboxButtonsDown[unsigned int(button)];
}

bool Input::isXboxButtonPressedNow(XboxButton button) const
{
	if (rangeCheck(unsigned int(button), XBOX_BUTTONS_RANGE)) return false;

	bool isButtonDownNow   = isXboxButtonDown(button);
	bool wasButtonUpBefore = !(m_xboxButtonsDownPreviously[unsigned int(button)]);

	bool res = isButtonDownNow && wasButtonUpBefore;

	return res;
}


bool Input::isXboxTriggerDown(XboxTrigger trigger, float threshold) const
{
	//Z LT positive, RT negative
	float z = sf::Joystick::getAxisPosition(0, sf::Joystick::Z);

	switch(trigger)
	{
	case XboxTrigger::LT:
	{
		return (z > threshold);
	}
		break;
	case XboxTrigger::RT:
	{
		return (z < -threshold);
	}
	break;
	}
}

Vec2f Input::getXboxStick(XboxStick stick) const
{
	auto axesToVector = [&](sf::Joystick::Axis xAxis, sf::Joystick::Axis yAxis)
	{
		float x = sf::Joystick::getAxisPosition(0, xAxis);
		if (fabsf(x) < XBOX_AXIS_MIN_THRESHOLD) x = 0.f;

		float y = sf::Joystick::getAxisPosition(0, yAxis);
		if (fabsf(y) < XBOX_AXIS_MIN_THRESHOLD) y = 0.f;

		return fw::Vec2f(x, y);
	};

	switch (stick)
	{
	case XboxStick::Left:
	{
		return axesToVector(
			sf::Joystick::Axis::X,
			sf::Joystick::Axis::Y
		);
	}
	break;
	case XboxStick::Right:
	{
		return axesToVector(
			sf::Joystick::Axis::U,
			sf::Joystick::Axis::V
		);
	}
	break;
	case XboxStick::DPad:
	{
		return axesToVector(
			sf::Joystick::Axis::PovX,
			sf::Joystick::Axis::PovY
		);
	}
	break;
	}
}

//
//  PRIVATE:
//


void Input::setKeyDown(int key)
{
	if (rangeCheck(key, KEYS_RANGE)) return;

	m_keysDown[key] = true;
}

void Input::setKeyUp(int key)
{
	if (rangeCheck(key, KEYS_RANGE)) return;

	m_keysDown[key] = false;
}

void Input::updateAnyKeyDown()
{
	for (int i = 0; i < KEYS_RANGE; ++i)
	{
		if (m_keysDown[i]) {
			m_anyKeyDown = true;
			return;
		}
	}
	m_anyKeyDown = false;
}


void Input::setMousePosX(int x)
{
	m_mouse.x = x;
}

void Input::setMousePosY(int y)
{
	m_mouse.y = y;
}

void Input::setMousePosition(int x, int y)
{
	setMousePosX(x);
	setMousePosY(y);
}

void Input::setMouseInWindow(bool in)
{
	m_mouse.inWindow = in;
}


void Input::setMouseLeftDown(bool down)
{
	m_mouse.left = down;
}

void Input::setMouseRightDown(bool down)
{
	m_mouse.right = down;
}

}