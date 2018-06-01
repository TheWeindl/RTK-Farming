#pragma once

#include "GPSPoint.h"
#include "SFML/Graphics.hpp"

class Traktor
{
public:
	Traktor();
	~Traktor();

	sf::CircleShape getShape();

#ifdef QT_VERSION	//defines the slot only if there is a Qt Version defined, which mean you are in qt creator
public slots:
#endif
	//Updates the current position of the tractor
	void updatePosition(double const & la, double const & lo);
	void updatePosition(GPSPoint const & position);

private:
	GPSPoint mPosition;
	sf::CircleShape mTriangle;
};

