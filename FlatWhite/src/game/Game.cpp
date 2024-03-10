#include "game/Game.hpp"

#include "system/DeltaClock.hpp"
#include "system/Window.hpp"

namespace fw
{

Game::Game()
    :
    m_currentSpace(NULL)
{
}

//
// INIT:
//

void Game::setWindowDimensions(int width, int height)
{
    m_windowData.width  = width;
    m_windowData.height = height;
}

void Game::setWindowTitle(std::string title)
{
    m_windowData.title = title;
}

void Game::addSpace(std::shared_ptr<Space> space)
{
    m_spaces.push_back(space);
}


//
// RUN:
//

void Game::run()
{
    auto window = std::make_shared<RenderWindow>(
        m_windowData.width,
        m_windowData.height,
        m_windowData.title
    );

    srand(time(NULL));

    DeltaClock deltaClock;

    Input input;

    if (m_spaces.empty())
    {
        throw m_spaces;
    }

    if (!m_currentSpace)
    {
        m_currentSpace = m_spaces[0];
    }

    while (window->isOpen())
    {
        input.perFrameUpdate();
        window->pollAllEvents(&input);

        m_currentSpace->handleInput(input);
        m_currentSpace->update(deltaClock.getDeltaTime());
        m_currentSpace->lateUpdate();

        window->clear();
        m_currentSpace->render(window.get());
        window->display();
    }

}

}