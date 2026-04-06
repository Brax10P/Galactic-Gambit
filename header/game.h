/**
 * @file game.h
 * @author Braxton, Hayden, & Felix
 * @brief header file for game
 * @version 0.1
 * @date 2026-04-06
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef GAME_H
#define GAME_H
#include "states.h"
#include "welcome.h"
#include "play.h"
#include "results.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Game
{
public:
    Game();
    ~Game(){};

    void handleInput(sf::RenderWindow& mWindow);
    void update(double elapsedTime, sf::RenderWindow& mWindow);
    void render(sf::RenderWindow& mWindow);
    //bool isDone() const;

private:
    //sf::RenderWindow mWindow;
    // bool mIsDone;
    State mGameState;
    Welcome mWelcomeScreen;
    Play mGame;
    Results mResults;
   
};

#endif
