#include "system/Input.hpp"

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

	if(sf::Joystick::isConnected(0))
	{
		//TODO ensure xbox data is reset when disconnected

		std::copy(std::begin(m_xboxButtonsDown), std::end(m_xboxButtonsDown), std::begin(m_xboxButtonsDownPreviously));
		
		for(auto const& pair : m_xBoxSticksPositions)
		{
			m_xBoxSticksPositionsPreviously[pair.first] = pair.second;
		}

		sf::Joystick::update();
		for(size_t i = 0; i < XBOX_BUTTONS_RANGE; ++i)
		{
			m_xboxButtonsDown[i] = sf::Joystick::isButtonPressed(0, unsigned int(i));
		}

		static auto axesToVector = [&](sf::Joystick::Axis xAxis, sf::Joystick::Axis yAxis)
		{
			float x = sf::Joystick::getAxisPosition(0, xAxis);
			if (fabsf(x) < XBOX_AXIS_MIN_THRESHOLD) x = 0.f;

			float y = sf::Joystick::getAxisPosition(0, yAxis);
			if (fabsf(y) < XBOX_AXIS_MIN_THRESHOLD) y = 0.f;

			return fw::Vec2f(x, y);
		};

		m_xBoxSticksPositions[XboxStick::Left] = axesToVector(
			sf::Joystick::Axis::X,
			sf::Joystick::Axis::Y
		);

		m_xBoxSticksPositions[XboxStick::Right] = axesToVector(
			sf::Joystick::Axis::U,
			sf::Joystick::Axis::V
		);

		static fw::Vec2f D_PAD_CORRECTOR = fw::Vec2f(0.f, -1.f);

		fw::Vec2f dPadAxesVector = axesToVector(
			sf::Joystick::Axis::PovX,
			sf::Joystick::Axis::PovY
		);

		m_xBoxSticksPositions[XboxStick::DPad] = fw::Vec2f(
			dPadAxesVector.x * D_PAD_CORRECTOR.x,
			dPadAxesVector.y * D_PAD_CORRECTOR.y
		);
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

bool indexIsOutOfRange(int index, int range)
{
	return index < 0 || index >= range;
}

bool Input::isKeyDown(int key) const
{
	if (indexIsOutOfRange(key, KEYS_RANGE)) return false;

	return m_keysDown[key];
}

bool Input::isKeyUp(int key) const
{
	if (indexIsOutOfRange(key, KEYS_RANGE)) return false;

	return !(m_keysDown[key]);
}

bool Input::isKeyPressedNow(int key) const
{
	if(indexIsOutOfRange(key, KEYS_RANGE)) return false;

	bool isKeyDownNow = isKeyDown(key);
	bool wasKeyUpBefore = !(m_keysDownPreviously[key]);

	bool res = isKeyDownNow && wasKeyUpBefore;

	return res;
}

bool Input::isAnyKeyPressedNow(const std::vector<Keyboard::Key>& keys) const
{
	for(const int& key : keys)
	{
		if(isKeyPressedNow(key)) return true;
	}

	return false;
}

bool Input::isAnyKeyDown() const
{
	return m_anyKeyDown;
}

bool Input::isAnyKeyDown(const std::vector<Keyboard::Key>& keys) const
{
	for(const int& key : keys)
	{
		if(isKeyDown(key)) return true;
	}

	return false;
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
	if(indexIsOutOfRange(unsigned int(button), XBOX_BUTTONS_RANGE)) return false;

	return m_xboxButtonsDown[unsigned int(button)];
}

bool Input::isXboxButtonPressedNow(XboxButton button) const
{
	if(indexIsOutOfRange(unsigned int(button), XBOX_BUTTONS_RANGE)) return false;

	bool isButtonDownNow   = isXboxButtonDown(button);
	bool wasButtonUpBefore = !(m_xboxButtonsDownPreviously[unsigned int(button)]);

	bool res = isButtonDownNow && wasButtonUpBefore;

	return res;
}

bool Input::isAnyXboxButtonPressedNow(const std::vector<XboxButton>& buttons) const
{
	for(const XboxButton& button : buttons)
	{
		if(isXboxButtonPressedNow(button)) return true;
	}

	return false;
}

bool Input::isAnyXboxButtonDown(const std::vector<XboxButton>& buttons) const
{
	for(const XboxButton& button : buttons)
	{
		if(isXboxButtonDown(button)) return true;
	}

	return false;
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
	return m_xBoxSticksPositions.at(stick);
}

Vec2f Input::getXboxStickIfExceededThresholdNow(XboxStick stick, float threshold) const
{
	Vec2f currentPosition = m_xBoxSticksPositions.at(stick);
	float magnitude = currentPosition.magnitude();

	if(magnitude >= threshold)
	{
		float previousMagnitude = m_xBoxSticksPositionsPreviously.at(stick).magnitude();
		if(previousMagnitude < threshold)
		{
			return currentPosition;
		}
	}

	return Vec2f::zero();
}

//
//  PRIVATE:
//


void Input::setKeyDown(int key)
{
	if(indexIsOutOfRange(key, KEYS_RANGE)) return;

	m_keysDown[key] = true;
}

void Input::setKeyUp(int key)
{
	if(indexIsOutOfRange(key, KEYS_RANGE)) return;

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