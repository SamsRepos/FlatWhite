#include "game/Game.hpp"

#include "system/DeltaClock.hpp"
#include "system/Window.hpp"

namespace fw
{

Game::Game()
    :
    m_currentSpace(NULL),
    m_moribund(false)
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

void Game::pushSpace(std::shared_ptr<Space> space)
{
    m_spacesStack.push(space);
    space->setGame(this);
    m_currentSpace = space;
}

void Game::popSpace()
{
    m_spacesStack.pop();

    if(m_spacesStack.size() > 0)
    {
        m_currentSpace = m_spacesStack.top();
    }
    else
    {
        m_moribund = true;
    }
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

    if(m_spacesStack.empty())
    {
        throw m_spacesStack;
    }

    if(!m_currentSpace)
    {
        m_currentSpace = m_spacesStack.top();
    }

    while(window->isOpen() && !m_moribund)
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

    if(window->isOpen())
    {
        window->close();
    }

}

}