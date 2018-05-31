#include "stdafx.h"
#include "Traktor.h"

#define PRINT_DEBUG

using namespace std;

Traktor::Traktor()
{
	mTriangle = sf::CircleShape(0.5f, 3);
	mTriangle.setFillColor(sf::Color::Red);	
	mTriangle.setOrigin(mTriangle.getRadius() ,0.0f);

#ifdef PRINT_DEBUG
	std::cout << "Origin Tractor: " << mTriangle.getOrigin().x << " " << mTriangle.getOrigin().x << std::endl;
#endif
}


Traktor::~Traktor()
{
}

void Traktor::updatePosition(double const & la, double const & lo)
{
	mPosition.mLat = la;
	mPosition.mLong = lo;
}

void Traktor::updatePosition(GPSPoint const & position)
{
	mPosition = position;
}

sf::CircleShape Traktor::getShape()
{
	int const mult = 10000;
	sf::Vector2f mapped;
	mapped.x = (float)(mPosition.mLat - (int)mPosition.mLat) * mult;
	mapped.y = (float)(mPosition.mLong - (int)mPosition.mLong) * mult;

	mTriangle.setPosition(mapped.x, mapped.y);

	return mTriangle;
}
