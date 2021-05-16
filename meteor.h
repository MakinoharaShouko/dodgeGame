#pragma once
#ifndef METEOR_H
#define METEOR_H
#include <SFML/Graphics.hpp>

using namespace sf;

class Meteor {
private:
	Vector2f _pos;  // the position of the meteor on screen
	double _speed;  // the speed it is traveling
	Text _symbol;  // the symbol of the meteor

public:
	Meteor(int x_range, double speed, const Font& font);

	// updates the meteor position
	// returns true if the meteor stays within range
	bool updatePos(double time, int y_range);

	// checks if the meteor collides with the ship
	bool collide(const FloatRect& ship) const;

	Text getSymbol() const;
};

#endif  // METEOR_H