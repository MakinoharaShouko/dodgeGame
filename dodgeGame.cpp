// HelloSFML.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <deque>
#include <iostream>
#include "Meteor.h"

using namespace std;
using namespace sf;

enum State {
	Play, Over
};

int main()
{
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	RenderWindow window(VideoMode(resolution.x, resolution.y), "DodgeGame", Style::Fullscreen);
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
			if (lastGenerate >= 20) {
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

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
