#include "../header/welcome.h"
Welcome::Welcome()
{
    if (!mFont.loadFromFile("assets/VintageCharm-Regular.otf"))
    {
        std::cout<<"Error opening file\n";
        exit(2);
    }
    mHeader.setFont(mFont);
    //choose the font size based on button size (I choose half)
    mHeader.setCharacterSize(20);
    // //set label
    mHeader.setString("Welcome to Galactic Gambit");

    mRules.setFont(mFont);
    //choose the font size based on button size (I choose half)
    mRules.setCharacterSize(16);
    // //set label
    mRules.setString("1. Beat the Dealer in Classic BlackJack!\n2. Don't Run out of Space Money!\n");
    mRules.setPosition({10, 30});

    mStart.setText("Start");
    mStart.setPosition({580, 450});
    mStart.setSize({60, 20});
    mStart.setColorTextNormal(sf::Color::Blue);
    //mStart.setColor(sf::Color(255,255,0));
}
State Welcome::handleInput(sf::Event& e, sf::RenderWindow& window)
{
    if (mStart.handleInput(e, window)){
        return game;
    }
    return welcome;
}
void Welcome::update()
{
    mStart.update();
}
void Welcome::render(sf::RenderWindow& window)
{
    window.draw(mHeader);
    window.draw(mRules);
    window.draw(mStart);
}