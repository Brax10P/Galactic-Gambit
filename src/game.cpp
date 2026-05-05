/**
 * @file game.cpp
 * @author Hayden, Braxton, Felix
 * @brief Handles welcome screen and game startup
 * @version 0.1
 * @date 2026-05-04
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "../header/game.h"

Game::Game()
{
    // mIsDone = false;
    mGameState = welcome;
}


/**
 * @brief Handles events from input devices and the window
 * 
 * @param window 
 */
void Game::handleInput(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            // Close window button clicked.
            window.close();
        }
        switch (mGameState)
        {
        case welcome:
        {
            State nextState = mWelcomeScreen.handleInput(event, window);

            if (nextState == game)
            {
                mGame.resetGame();
            }

            mGameState = nextState;
            break;
        }
        case game:
            // std::cout<<"Game::handleInput case game" <<std::endl;
            mGameState = mGame.handleInput(event, window);
            break;
        case howTo:
            mGameState = mHowTo.handleInput(event, window);
            break;

        case results:
            // std::cout<<"Game::handleInput case result" <<std::endl;
            mGameState = mResults.handleInput(event, window);
            break;
        case quit:
            // std::cout<<"Game::handleInput case quit" <<std::endl;
            window.close();
            break;
        }
    }
}

/**
 * @brief Updates objects in the scene
 * 
 * @param elapsedTime 
 * @param window 
 */
void Game::update(double elapsedTime, sf::RenderWindow &window)
{
    switch (mGameState)
    {
    case welcome:
        // std::cout<<"Game::update case welcome" <<std::endl;
        mWelcomeScreen.update();
        break;
    case game:
        mGame.update(elapsedTime, window);

        if (mGame.shouldReturnToWelcome())
        {
            mGameState = welcome;
        }
        break;
    case results:
        // std::cout<<"Game::update case result" <<std::endl;
        mResults.update();
        break;
    case howTo:
        mHowTo.update();
        break;

    case quit:
        // std::cout<<"Game::update case quit" <<std::endl;
        window.close();
        break;
    }
}


/**
 * @brief Renders objects from the scene onto the window
 * 
 * @param window 
 */
void Game::render(sf::RenderWindow &window)
{
    window.clear(sf::Color::Black);
    // mWindow.draw(mCherryPlant);
    switch (mGameState)
    {
    case welcome:
        mWelcomeScreen.render(window);
        break;
    case game:
        mGame.render(window);
        break;
    case results:
        mResults.render(window);
        break;
    case howTo:
        mHowTo.render(window);
        break;
    case quit:
        break;
    }
    window.display();
}
