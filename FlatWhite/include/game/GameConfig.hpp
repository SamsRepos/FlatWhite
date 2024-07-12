#pragma once

namespace fw
{

const int DEFAULT_WINDOW_WIDTH = 1366;
const int DEFAULT_WINDOW_HEIGHT = 768;

const std::string DEFAULT_WINDOW_TITLE = "FlatWhite Framework";

const bool DEFAULT_START_FULLSCREEN      = false;
const bool DEFAULT_FULL_SCREEN_TOGGLABLE = false;
const bool DEFAULT_WINDOW_ADJUSTABLE     = false;

struct GameConfig
{
public:
    int windowWidth         = DEFAULT_WINDOW_WIDTH;
    int windowHeight        = DEFAULT_WINDOW_HEIGHT;

    std::string windowTitle = DEFAULT_WINDOW_TITLE;

    bool startFullscreen     = DEFAULT_START_FULLSCREEN;
    bool fullScreenTogglable = DEFAULT_FULL_SCREEN_TOGGLABLE;
    bool windowAdjustable    = DEFAULT_WINDOW_ADJUSTABLE;
};

}