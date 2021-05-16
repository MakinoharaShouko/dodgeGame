#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <deque>
#include <iostream>
#include "meteor.h"

using namespace std;
using namespace sf;

enum State {
	Play, Over
};

int main(int argc, char** argv)
{
	Vector2f resolution;
	uint32_t style;
	if (argc == 3) {
		resolution.x = atof(argv[1]);
		resolution.y = atof(argv[2]);
		style = Style::Resize;
	} else {
		resolution.x = VideoMode::getDesktopMode().width;
		resolution.y = VideoMode::getDesktopMode().height;
		style = Style::Fullscreen;
	}
	RenderWindow window(VideoMode(resolution.x, resolution.y), "DodgeGame", style);

	window.setFramerateLimit(60);
	View mainView(FloatRect(0, 0, resolution.x, resolution.y));

	State state = Play;

	Font font;
	font.loadFromFile("Font/font.ttf");

	float meteorSpeed = 1;
	float shipSpeed = 1;
	deque<Meteor> meteors;

	// creates a space ship
	Text ship;
	Vector2f shipPos;
	shipPos.x = resolution.x / 2;
	shipPos.y = resolution.y / 5 * 4;
	ship.setFillColor(Color::White);
	ship.setPosition(shipPos);
	ship.setString("*");
	ship.setCharacterSize(30);
	ship.setFont(font);

	Clock clk;
	clk.restart();
	double lastGenerate = 0;
	int score = 0;
	Text scoreMessage;
	scoreMessage.setFont(font);
	scoreMessage.setCharacterSize(50);
	scoreMessage.setFillColor(Color::Red);

	// game bgm
	SoundBuffer bufferBGM;
	bufferBGM.loadFromFile("Music/orphans.wav");
	Sound soundBGM;
	soundBGM.setBuffer(bufferBGM);
	soundBGM.setLoop(true);
	soundBGM.play();

	while (window.isOpen()) {  // main game loop
		// Quit game
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();

		// User controls the ship motion horizontally
		if (state == Play) {
			float t = clk.restart().asMilliseconds();
			if (Keyboard::isKeyPressed(Keyboard::A) && shipPos.x > 0)
				shipPos.x -= shipSpeed * t;

			if (Keyboard::isKeyPressed(Keyboard::D) && shipPos.x < resolution.x - 1)
				shipPos.x += shipSpeed * t;
			ship.setPosition(shipPos);

			int meteorsLength = meteors.size();
			for (int i = 0; i < meteorsLength; i ++) {
				Meteor meteor = meteors.front();
				meteors.pop_front();
				if (meteor.updatePos(t, resolution.y))
					meteors.push_back(meteor);
				else
					score++;
				if (meteor.collide(ship.getGlobalBounds())) {
					// ship collides
					state = Over;
					ship.setString('x');
					scoreMessage.setString("YOU DIED. SCORE: " + to_string(score / 10));
					FloatRect messageBound = scoreMessage.getLocalBounds();
					scoreMessage.setOrigin(messageBound.width / 2, messageBound.height / 2);
					scoreMessage.setPosition(resolution.x / 2, resolution.y / 2);
					break;
				}
			}

			lastGenerate += t;
			// addjust difficulty based on window size
			if (lastGenerate >= 40000 / resolution.x) {
				// generates a new meteor
				Meteor newMeteor(resolution.x, meteorSpeed, font);
				meteors.push_back(newMeteor);
				lastGenerate = 0;  // reset time for generation
			}
		}
		if (state == Over) {
			if (Keyboard::isKeyPressed(Keyboard::Space)) {  // new game
				ship.setString('*');
				shipPos.x = resolution.x / 2;
				ship.setPosition(shipPos);
				meteors.clear();
				score = 0;
				state = Play;
				soundBGM.play();
			}
		}

		// update the view
		window.clear();
		window.draw(ship);
		for (auto meteor : meteors)
			window.draw(meteor.getSymbol());
		if (state == Over)
			window.draw(scoreMessage);
		//cout << meteors.size() << endl;
		window.display();
	}
}