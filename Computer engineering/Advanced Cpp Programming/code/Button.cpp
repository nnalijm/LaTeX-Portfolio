#include "Button.h"

Button::Button(float W, float H, string shribeName) : MyText(shribeName) {
	w = W;
	h = H;
	press = false;
	button.setSize(Vector2f(W, H));
	txt.setPosition(button.getPosition());
}

void Button::sleditForSprite(Sprite& s, float x, float y) {
	button.setPosition(s.getPosition().x + x, s.getPosition().y + y);
	txt.setPosition(s.getPosition().x + x, s.getPosition().y + y);
}

void Button::draw(RenderWindow& window) {
	txt.setPosition(button.getPosition());
	window.draw(button);
	window.draw(txt);
}

bool Button::pressed(Event& event, Vector2i mousePosition) {
	if (button.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && event.type == Event::MouseButtonPressed && !press) {
		if (event.key.code == Mouse::Left) {
			press = true;
			return true;
		}
	}

	if (!press) return false;

	if (press) {
		if (!(event.type == Event::MouseButtonPressed)) {
			press = false;
		}
		return false;
	}

	return false;
}

bool Button::navediaMouse(Event& event, Vector2i mousePosition) {
	return button.getGlobalBounds().contains(mousePosition.x, mousePosition.y);
}

void Button::getSound(string failAudio) {
	buffer.loadFromFile(failAudio);
	sound.setBuffer(buffer);
}

void Button::soundPlay() {
	sound.play();
}

void Button::soundSetVolume(int volume) {
	sound.setVolume(volume);
}

void Button::setButtonSize(float W, float H) {
	w = W;
	h = H;
	button.setSize(Vector2f(W, H));
}

void Button::setOringCenter() {
	button.setOrigin(w / 2, h / 2);
}

void Button::setPosition(float x, float y) {
	button.setPosition(x, y);
}

void Button::setFillRacktengelColor(float R, float G, float B) {
	button.setFillColor(Color(R, G, B));
}


