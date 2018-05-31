#pragma once

#include "GPSPoint.h"
#include "SFML/Graphics.hpp"

class Traktor
{
public:
	Traktor();
	~Traktor();

	//Updates the current position of the tractor
	void updatePosition(double const & la, double const & lo);
	void updatePosition(GPSPoint const & position);

	sf::CircleShape getShape();

private:
	GPSPoint mPosition;
	sf::CircleShape mTriangle;
};

