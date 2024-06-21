#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class MyText {
private:
    string shribe;
    Font font;

public:
    sf::Text txt;

    MyText(string shribeName);

    MyText();

    void sleditForSprite(Sprite& s, float x, float y);

    void getChislo(float n);

    void setString(string name);

    void setPosition(float x, float y);

    void setFillTextColor(float R, float G, float B);

    void setCharacterSize(float a);

    void draw(RenderWindow& window);
};

#endif // TEXT_H
