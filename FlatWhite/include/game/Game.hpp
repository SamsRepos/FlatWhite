#pragma once

#include "space/Space.hpp"

#include <vector>
#include <string>
#include <stack>

const int DEFAULT_WINDOW_WIDTH = 1366;
const int DEFAULT_WINDOW_HEIGHT = 768;
const std::string DEFAULT_WINDOW_TITLE = "FlatWhite";

namespace fw
{

class Game
{
public:
    Game();

    // init:
    void setWindowDimensions(int width, int height);
    void setWindowTitle(std::string title);

    void pushSpace(std::shared_ptr<Space> space);

    void popSpace();

    // run:
    void run();

private:
    std::stack<std::shared_ptr<Space>> m_spacesStack;
    std::shared_ptr<Space> m_currentSpace;

    struct WindowData 
    {
        int width         = DEFAULT_WINDOW_WIDTH;
        int height        = DEFAULT_WINDOW_HEIGHT;
        std::string title = DEFAULT_WINDOW_TITLE;
    };
    WindowData m_windowData;

    bool m_moribund;
};

}