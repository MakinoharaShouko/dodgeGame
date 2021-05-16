#include "pch.h"
#include "meteor.h"

Meteor::Meteor(int x_range, double speed, const Font& font) {
	_pos.x = rand() % x_range;
	_pos.y = 0;  // spawn at the top of the screen
	_symbol.setFillColor(Color::White);
	_symbol.setPosition(_pos);
	_symbol.setFont(font);
	_symbol.setString("-");
	_symbol.setCharacterSize(30);
	_speed = speed;
}

bool Meteor::updatePos(double time, int y_range) {
	_pos.y += time * _speed;
	_symbol.setPosition(_pos);
	if (_pos.y >= y_range)  // out of screen range
		return false;
	return true;
}

bool Meteor::collide(const FloatRect& ship) const {
	return ship.intersects(_symbol.getGlobalBounds());
}

Text Meteor::getSymbol() const {
	return _symbol;
}