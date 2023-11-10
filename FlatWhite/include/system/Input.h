#pragma once

#include <SFML/Window/Event.hpp>

#include "common/Vec2f.h"

namespace fw
{

	const size_t KEYS_RANGE = 256;

	class Input
	{
	public:
		static bool eventIsInput(const sf::Event& event);
		void perFrameUpdate();
		void eventUpdate(const sf::Event& event);

		bool isKeyDown(int key) const;
		bool isKeyUp(int key) const;
		bool isKeyPressedNow(int key) const;
		bool isAnyKeyDown() const;

		int getMousePosX() const;
		int getMousePosY() const;
		Vec2f getMousePosition() const;
		inline bool isMouseInWindow() const;

		bool isMouseLeftDown() const;
		bool isMouseRightDown() const;
		bool isMouseLeftClickedNow() const;
		bool isMouseRightClickedNow() const;

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

		void debugOut();

		//void setMouseWheelDelta();

		bool m_keysDown[KEYS_RANGE]{ false };
		bool m_keysDownPreviously[KEYS_RANGE]{ false };
		bool m_keysPressedNow[KEYS_RANGE]{ false };
		bool m_anyKeyDown = false;

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