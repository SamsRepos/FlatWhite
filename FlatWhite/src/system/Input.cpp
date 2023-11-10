#include "system/Input.h"

#include <iostream>

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
bool keysRangeCheck(int key)
{
	return key < 0 || key >= KEYS_RANGE;
}

bool Input::isKeyDown(int key) const
{
	if (keysRangeCheck(key)) return false;

	return m_keysDown[key];
}

bool Input::isKeyUp(int key) const
{
	if (keysRangeCheck(key)) return false;

	return !(m_keysDown[key]);
}

bool Input::isKeyPressedNow(int key) const
{
	if (keysRangeCheck(key)) return false;
	
	bool isKeyDownNow    = isKeyDown(key);
	bool wasKeyUpBefore  = !(m_keysDownPreviously[key]);

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

//
//  PRIVATE:
//


void Input::setKeyDown(int key)
{
	if (keysRangeCheck(key)) return;

	m_keysDown[key] = true;
}

void Input::setKeyUp(int key)
{
	if (keysRangeCheck(key)) return;

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

void Input::debugOut()
{
	std::cout << "Mouse x: " << m_mouse.x << " ";
	std::cout << "Mouse y: " << m_mouse.y << " ";
	std::cout << std::endl;
}