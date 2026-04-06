/**
 * @file main.cpp
 * @author Braxton, Hayden, & Felix
 * @brief This is our final project, Galactic Gambit
 * @version 0.1
 * @date 2026-04-06
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "../header/game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Galactic Gambit");
    window.setPosition({50,50});
    Game game;
   
    sf::Clock clock; 

    while(window.isOpen())
    {
        float dt=clock.restart().asSeconds();
        game.handleInput(window);
        game.update(dt, window);
        game.render(window);
    }

    return 0;
}
// Gameplay Loop:
// 1. Start by asking player amount to bet
// 2. Deals cards for both dealer and player (hides one of the dealer's cards)
// 	If player has Blackjack(21), deal out cash and start at #1
// 	If Dealer has Blackjack, stop gameplay and start at #1
// 3. Asks the player if they want to hit, stand, or double down
// 4. If hit, deal new card for player and see if it goes over 21
// 	If not, ask if they want to hit or stand
// 		If Stand, move to step #5
// 		If Hit, start at # 6 again until stand
// 	If stand, move to step #5
// 	If Double down, deal one card, double bet, and move to step #9
// 5. Show dealer's hidden card and compare to value of Player's cards
// 	If Dealer is higher, take players bet and start at #1
// 	If Player is higher, add to total $$$ player has and start at #1
