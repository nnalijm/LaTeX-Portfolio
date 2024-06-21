#include "MyText.h"

MyText::MyText(string shribeName) {
	font.loadFromFile("fonts/bloodcrow.ttf");
	txt.setFont(font);
	txt.setCharacterSize(20);
	txt.setFillColor(Color(0, 0, 0));
	shribe = shribeName;
	txt.setString(shribe);
}

MyText::MyText() {
	font.loadFromFile("fonts/bloodcrow.ttf");
	txt.setFont(font);
	txt.setCharacterSize(20);
	txt.setFillColor(Color(0, 0, 0));
	shribe = "";
	txt.setString(shribe);
}


void MyText::sleditForSprite(Sprite& s, float x, float y) {
	txt.setPosition(s.getPosition().x + x, s.getPosition().y + y);
}

void MyText::getChislo(float n) {
	ostringstream chislo;
	chislo << n;
	txt.setString(shribe + chislo.str());
}

void MyText::setString(string name) {
	txt.setString(name);
}

void MyText::setPosition(float x, float y) {
	txt.setPosition(x, y);
}

void MyText::setFillTextColor(float R, float G, float B) {
	txt.setFillColor(Color(R, G, B));
}

void MyText::setCharacterSize(float a) {
	txt.setCharacterSize(a);
}

void MyText::draw(RenderWindow& window) {
	window.draw(txt);
}


/*
int main()
{

	RenderWindow window(sf::VideoMode(920, 700), "My window");


	MyText a("lol:  ");
	a.setFillTextColor(0, 255, 0);
	a.setPosition(200, 200);






	Clock clock;

	while (window.isOpen())
	{

		Vector2i mouse = Mouse::getPosition(window);
		Vector2f mousePositon = window.mapPixelToCoords(mouse);//переводим их в игровые (уходим от коорд окна)



		float time = clock.getElapsedTime().asSeconds();

		//clock.restart();

		//time = time / 800;



		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		window.clear(Color(0, 0, 0));


		a.getChislo(int(time));

		a.draw(window);



		window.display();
	}


	
	return 0;
}*/