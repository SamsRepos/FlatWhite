#pragma once

#include "space/Space.hpp"
#include "GameConfig.hpp"

#include <vector>
#include <string>
#include <stack>


namespace fw
{

class RenderWindow;

class Game
{
public:
    Game(const GameConfig& gameConfig);

    void pushSpace(std::shared_ptr<Space> space);

    void popSpace();

    // run:
    void run();

private:
    GameConfig m_gameConfig;

    std::stack<std::shared_ptr<Space>> m_spacesStack;
    std::shared_ptr<Space> m_currentSpace;

    bool m_moribund;

    std::shared_ptr<RenderWindow> m_window;
    bool m_isFullScreenNow;

    void toggleFullscreen();
};

}