#include "../header/welcome.h"
Welcome::Welcome()
{
    mBackDrop.setSize(sf::Vector2f(1280.f, 720.f));
    if (!mBackground.loadFromFile("assets/Background 1.png"))
    {
        std::cout << "Error opening background file\n";
        exit(2);
    }

    mBackDrop.setTexture(&mBackground);
    if (!mFont.loadFromFile("assets/VintageCharm-Regular.otf"))
    {
        std::cout<<"Error opening file\n";
        exit(2);
    }
    mHeader.setFont(mFont);
    //choose the font size based on button size (I choose half)
    mHeader.setCharacterSize(60);
    // //set label
    mHeader.setString("Welcome to Galactic Gambit!");
    mHeader.setPosition({250,350});

    mRules.setFont(mFont);
    //choose the font size based on button size (I choose half)
    mRules.setCharacterSize(40);
    // //set label
    mRules.setString("1. Beat the Dealer in Classic BlackJack!\n2. Don't Run out of Space Money!\n");
    mRules.setPosition({300, 420});

    mStart.setText("Start");
    mStart.setPosition({1000, 580});
    mStart.setSize({150,150});
    mStart.setColorTextNormal(sf::Color::Blue);

    mHowTo.setText("How to Play");
    mHowTo.setPosition({280, 580});
    mHowTo.setSize({150,150});
    mHowTo.setColorTextNormal(sf::Color::Blue);
    //mStart.setColor(sf::Color(255,255,0));
}
State Welcome::handleInput(sf::Event& e, sf::RenderWindow& window)
{
    if (mStart.handleInput(e, window))
    {
        return game;
    }
    if(mHowTo.handleInput(e,window))
    {
        return howTo;
    }
    return welcome;
}
void Welcome::update()
{
    mStart.update();
    mHowTo.update();
}
void Welcome::render(sf::RenderWindow& window)
{
    window.draw(mBackDrop);
    window.draw(mHeader);
    window.draw(mRules);
    window.draw(mHowTo);
    window.draw(mStart);
}