#include "game/Game.hpp"

#include "system/DeltaClock.hpp"
#include "system/Window.hpp"



namespace fw
{
    namespace
    {
        bool isToggleFullscreenNow(const Input& input)
        {
            if((input.isKeyDown(Keyboard::LAlt) || input.isKeyDown(Keyboard::RAlt)) && input.isKeyPressedNow(Keyboard::Enter))
            {
                return true;
            }

            if(input.isKeyPressedNow(Keyboard::F11))
            {
                return true;
            }

            return false;
        }
    }

Game::Game(const GameConfig& gameConfig)
    :
    m_currentSpace(NULL),
    m_moribund(false),
    m_gameConfig(gameConfig)
{
}

//
// INIT:
//

void Game::pushSpace(std::shared_ptr<Space> space)
{
    m_spacesStack.push(space);
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
    m_window = std::make_shared<RenderWindow>(
        m_gameConfig.windowWidth,
        m_gameConfig.windowHeight,
        m_gameConfig.windowTitle,
        m_gameConfig.startFullscreen,
        m_gameConfig.windowAdjustable
    );

    m_isFullScreenNow = m_gameConfig.startFullscreen;

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

    while(m_window->isOpen() && !m_moribund)
    {
        input.perFrameUpdate();
        m_window->pollAllEvents(&input);

        if(m_gameConfig.fullScreenTogglable && isToggleFullscreenNow(input))
        {
            toggleFullscreen();
        }

        m_currentSpace->handleInput(input);
        m_currentSpace->update(deltaClock.getDeltaTime());
        m_currentSpace->lateUpdate();

        if(m_currentSpace->isMoribund())
        {
            popSpace();
        }

        m_window->clear();
        m_currentSpace->render(m_window.get());
        m_window->display();
    }

    if(m_window->isOpen())
    {
        m_window->close();
    }

}


//
// PRIVATE:
//

void Game::toggleFullscreen()
{
    m_window = std::make_shared<RenderWindow>(
        m_gameConfig.windowWidth,
        m_gameConfig.windowHeight,
        m_gameConfig.windowTitle,
        !m_isFullScreenNow,
        m_gameConfig.windowAdjustable
    );

    m_isFullScreenNow = !m_isFullScreenNow;
}

}