#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include "sfml/GPSPoint.h"

class Field
{

public:
	///////////////////////////////////////////////////////////////////////////
	//CTOR - DTOR
	Field();
	Field(std::vector<GPSPoint> const & corners);
	~Field();

	///////////////////////////////////////////////////////////////////////////
	//OPERATORS
	friend std::ostream& operator<< (std::ostream& out, Field& field);

	///////////////////////////////////////////////////////////////////////////
	//PUBLIC FUNCTIONS

	//Returns the sfml shape of the field
	sf::ConvexShape& getShape();

	//Returns the vector with all the corners of the field
	std::vector<GPSPoint>& getCorners();

	//Sets the origin of the sfml shape
	void setPos(float const & x, float const y);	

	//Prints the lengths between the corners of the fields
	void printEdgeLengths();

private:
	///////////////////////////////////////////////////////////////////////////
	//PRIVATE MEMBER
	sf::ConvexShape mShape;
	std::vector<GPSPoint> mCorners;

	///////////////////////////////////////////////////////////////////////////
	//PRIVATE FUNCTIONS

	//Converts the models calculation coordinates to sfml coordinats for rendering
	sf::Vector2f mapToSFML(double const lat, double const lo);

	//Calculates the distance in meters between two position (haversinus)
	double calcDistance(double lat1, double long1, double lat2, double long2);
	double calcDistance(GPSPoint& p1, GPSPoint p2);
};

