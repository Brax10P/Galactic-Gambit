#include "../header/game.h"

Game::Game()
{
    //mIsDone = false;
    mGameState = welcome;
}

//Handle events from input devices and the window
void Game::handleInput(sf::RenderWindow& window)
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            // Close window button clicked.
            window.close();
        }
        switch (mGameState)
        {
        case welcome:
//std::cout<<"Game::handleInput case welcome" <<std::endl;
            mGameState = mWelcomeScreen.handleInput(event, window);
            break;
        case game:
//std::cout<<"Game::handleInput case game" <<std::endl;
            mGameState = mGame.handleInput(event, window);
            break;
        case results:
//std::cout<<"Game::handleInput case result" <<std::endl;
            mGameState=mResults.handleInput(event, window);
            break;
        case quit:
//std::cout<<"Game::handleInput case quit" <<std::endl;
            window.close();
            break;            
        }
    }
}

//Update objects in the scene
void Game::update(double elapsedTime, sf::RenderWindow& window)
{
    switch (mGameState)
        {
        case welcome:
//std::cout<<"Game::update case welcome" <<std::endl;
            mWelcomeScreen.update();
            break;
        case game:
//std::cout<<"Game::update case game" <<std::endl;
            mGame.update(elapsedTime, window);
            break;
        case results:
//std::cout<<"Game::update case result" <<std::endl;
            mResults.update();
            break;
        case quit:
//std::cout<<"Game::update case quit" <<std::endl;
            window.close();
            break;            
        }
}


//Render objects from the scene onto the window
void Game::render(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);
    //mWindow.draw(mCherryPlant);
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
        case quit:
            break;          
        }
    window.display();
}

Deck::Deck()
{
    setupDeck();
}

void Deck::setupDeck()
{
    unsigned deckShuffle = std::chrono::system_clock::now().time_since_epoch().count();
                            // Pretty much this will randomize the deck using
                            // the time in miliseconds as a seed
                            // mainly used this to be able to keep the shuffle
                            // the exact same for both so a 2 card doesn't end up with 11

    vector<int> cardValue = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11, 
                             2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11, 
                             2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11,
                             2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
                            // First line is first suite, second is second suite, so on so forth
    
    loadcardSprites();

    shuffle(cardValue.begin(), cardValue.end(), std::default_random_engine(deckShuffle));
    shuffle(cardSprites.begin(), cardSprites.end(), std::default_random_engine(deckShuffle));
}

void Deck::loadcardSprites()
{
    // section out cards from sprite sheet and store them in cardSprite vector
    cardSpriteSheet.loadFromFile("assets/galactic_gambit_cards.png");

    for(int i = 0; i < 4; i++)
    {
        // These two are for adding the difference in the for loops
        // just added them here for simplicity sake, if we want to make them
        // private variables that is an option as well
        int xDiff = 0;

        // for loops below loading in one line, jumping to next, loading in next
        // there is a 41 pixel difference between each card horizontally
        for(int j = 0; j < 13; j++) // clubs being loaded
        {
            sf::RectangleShape cardSprite;
            cardSprite.setTexture(&cardSpriteSheet);
            cardSprite.setTextureRect(sf::IntRect((10 + xDiff), (16), (43 + xDiff), (62)));
            cardSprite.setOrigin((27.f + xDiff), (39.f));
            cardSprites.push_back(cardSprite);
            xDiff = xDiff + 41;
        }
        xDiff = 0;

        for(int j = 0; j < 13; j++) // hearts being loaded
        {
            sf::RectangleShape cardSprite;
            cardSprite.setTexture(&cardSpriteSheet);
            cardSprite.setTextureRect(sf::IntRect((10 + xDiff), (68), (43 + xDiff), (113)));
            cardSprite.setOrigin(27.f + xDiff, 90.f);
            cardSprites.push_back(cardSprite);
            xDiff = xDiff + 41;
        }
        xDiff = 0;

        for(int j = 0; j < 13; j++) // spades being loaded
        {
            sf::RectangleShape cardSprite;
            cardSprite.setTexture(&cardSpriteSheet);
            cardSprite.setTextureRect(sf::IntRect((10 + xDiff), (121), (43 + xDiff), (166)));
            cardSprite.setOrigin((27.f + xDiff), 143.f);
            cardSprites.push_back(cardSprite);
            xDiff = xDiff + 41;
        }
        xDiff = 0;

        for(int j = 0; j < 13; j++) // diamonds being loaded
        {
            sf::RectangleShape cardSprite;
            cardSprite.setTexture(&cardSpriteSheet);
            cardSprite.setTextureRect(sf::IntRect((10 + xDiff), (121), (43 + xDiff), (166)));
            cardSprite.setOrigin((27.f + xDiff), 197.f);
            cardSprites.push_back(cardSprite);
            xDiff = xDiff + 41;
        }
    }
}

//Check if game is done, right now, we just checked if window is still open
// bool Game::isDone() const
// {
//     return (!mWindow.isOpen());
// }
