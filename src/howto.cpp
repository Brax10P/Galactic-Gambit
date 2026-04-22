#include "../header/howto.h"
HowTo::HowTo()
{
    mBackDrop.setSize(sf::Vector2f(1280.f, 720.f));
    if (!mBackground.loadFromFile("assets/testhow.png"))
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
    mRules.setFont(mFont);
    //choose the font size based on button size (I choose half)
    mRules.setCharacterSize(50);
    // //set label
    mRules.setString("Rules for Galactic Gambit!");
    mRules.setPosition({325,75});

    mValues.setFont(mFont);
    //choose the font size based on button size (I choose half)
    mValues.setCharacterSize(35);
    // //set label
    mValues.setString("1. The Dealer Draws on 16 and Stands on 17\n2. If you run out of space money, GAME OVER\n3. Get as close to 21 without going over.\n4. Beat the Dealer and YOU WIN\n5. Card Values Found Below");
    mValues.setPosition({275, 150});

    mBack.setText("Go Back");
    mBack.setPosition({1200, 610});
    mBack.setSize({150,150});
    mBack.setTextSize(30);
    mBack.setColorTextNormal(sf::Color::White);


}
State HowTo::handleInput(sf::Event& e, sf::RenderWindow& window)
{
    if (mBack.handleInput(e, window))
    {
        return welcome;
    }
    return howTo;
}
void HowTo::update()
{
    mBack.update();
}
void HowTo::render(sf::RenderWindow& window)
{
    window.draw(mBackDrop);
    window.draw(mBack);
    window.draw(mRules);
    window.draw(mValues);
}