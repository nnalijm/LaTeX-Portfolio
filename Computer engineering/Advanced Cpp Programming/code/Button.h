#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MyText.h"

using namespace std;
using namespace sf;

class Button : public MyText {
private:
    float w, h;
    SoundBuffer buffer;
    Sound sound;
    bool press;

public:
    RectangleShape button;

    Button(float W, float H, string shribeName);

    void sleditForSprite(Sprite& s, float x, float y);

    void draw(RenderWindow& window);

    bool pressed(Event& event, Vector2i mousePosition);

    bool navediaMouse(Event& event, Vector2i mousePosition);

    void getSound(string failAudio);

    void soundPlay();

    void soundSetVolume(int volume);

    void setButtonSize(float W, float H);

    void setOringCenter();

    void setPosition(float x, float y);

    void setFillRacktengelColor(float R, float G, float B);
};

#endif // BUTTON_H
