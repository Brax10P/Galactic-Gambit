#include "catch_amalgamated.hpp"
#include "../header/play.h"



TEST_CASE("Play initializes money and bet values correctly", "[Play initialization]")
{
    Play game;

    REQUIRE(game.getPlayerMoney() == 500);
    REQUIRE(game.getCurrentBet() == 0);
    REQUIRE(game.getPlayerScore() == 0);
    REQUIRE(game.getDealerScore() == 0);
    REQUIRE(game.getBettingPhase() == true);
    REQUIRE(game.getRoundOver() == false);
}


TEST_CASE("resetGame resets money, bet, scores, and game state", "[resetGame]")
{
    Play game;

    game.resetGame();

    REQUIRE(game.getPlayerMoney() == 500);
    REQUIRE(game.getCurrentBet() == 0);
    REQUIRE(game.getPlayerScore() == 0);
    REQUIRE(game.getDealerScore() == 0);
    REQUIRE(game.getBettingPhase() == true);
    REQUIRE(game.getRoundOver() == false);
    REQUIRE(game.getResultMessage() == "");
}

TEST_CASE("dealPlayerHand removes two cards from deck value vector", "[deck]")
{
    Play game;

    int startingDeckSize = game.getDeckSize();

    game.dealPlayerHand();

    int endingDeckSize = game.getDeckSize();

    REQUIRE(startingDeckSize == 52);
    REQUIRE(endingDeckSize == 50);
}


TEST_CASE("dealPlayerHand gives player two cards and updates score", "[dealPlayerHand]")
{
    Play game;

    game.dealPlayerHand();

    REQUIRE(game.getPlayerCardCount() == 0); 
    REQUIRE(game.getPlayerScore() > 0);

    sf::Vector2f cardOnePos = game.getCardOnePosition();
    sf::Vector2f cardTwoPos = game.getCardTwoPosition();

    REQUIRE(cardOnePos.x == 575);
    REQUIRE(cardOnePos.y == 500);

    REQUIRE(cardTwoPos.x == 650);
    REQUIRE(cardTwoPos.y == 500);
}


TEST_CASE("dealDealerHand gives dealer two cards and updates score", "[dealDealerHand]")
{
    Play game;

    game.dealDealerHand();

    REQUIRE(game.getDealerScore() > 0);

    sf::Vector2f cardOnePos = game.getDealerCardOnePosition();
    sf::Vector2f cardTwoPos = game.getDealerCardTwoPosition();

    REQUIRE(cardOnePos.x == 575);
    REQUIRE(cardOnePos.y == 325);

    REQUIRE(cardTwoPos.x == 650);
    REQUIRE(cardTwoPos.y == 325);
}

TEST_CASE("dealPlayerHand adds known card values to player score", "[known cards]")
{
    Play game;

    game.setDeckForTest({10, 7});

    game.dealPlayerHand();

    REQUIRE(game.getPlayerScore() == 17);
    REQUIRE(game.getDeckSize() == 0);
}

TEST_CASE("dealPlayerHand counts ace as 11 initially", "[known cards]")
{
    Play game;

    game.setDeckForTest({9, 11});   

    game.dealPlayerHand();

    REQUIRE(game.getPlayerScore() == 20);
    REQUIRE(game.getDeckSize() == 0);
}

TEST_CASE("drawAnotherCard reduces ace value if a bust would occur", "[known cards]")
{
    Play game;

    game.setDeckForTest({5, 9, 11});    // 9 not 2

    game.dealPlayerHand();

    REQUIRE(game.getPlayerScore() == 20);

    game.drawAnotherCard();

    REQUIRE(game.getPlayerScore() == 15);
    REQUIRE(game.getDeckSize() == 0);
}



