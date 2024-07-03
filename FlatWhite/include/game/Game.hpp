#pragma once

#include "space/Space.hpp"

#include <vector>
#include <string>

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

    void addSpace(std::shared_ptr<Space> space);

    void setCurrentSpace(size_t index);

    void setCurrentSpace(std::shared_ptr<Space> space);

    // run:
    void run();

private:
    std::vector<std::shared_ptr<Space>> m_spaces;
    std::shared_ptr<Space> m_currentSpace;

    struct WindowData 
    {
        int width         = DEFAULT_WINDOW_WIDTH;
        int height        = DEFAULT_WINDOW_HEIGHT;
        std::string title = DEFAULT_WINDOW_TITLE;
    };
    WindowData m_windowData;
};

}