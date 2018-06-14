//#include "src/stdafx.h"
#include "sfml/Field.h"

#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <math.h>

#define d2r ( M_PI/ 180.0)
#define PRINT_DEBUG

Field::Field()
{
}

Field::Field(std::vector<GPSPoint> const & corners)
{
	//Set coordinates of the corners
	for(size_t i = 0; i < corners.size(); i++)
	{
		mCorners.push_back(GPSPoint(corners[i].mLat, corners[i].mLong));
	}

	//Create the sfml shape
	mShape = sf::ConvexShape();
	mShape.setPointCount(mCorners.size());


#ifdef PRINT_DEBUG
	std::cout << "Origin Field: " << mShape.getOrigin().x  << " " << mShape.getOrigin().x << std::endl;
#endif

	for (size_t i = 0; i < mCorners.size(); i++)
	{
		sf::Vector2f point = mapToSFML(mCorners[i].mLat, mCorners[i].mLong);
		mShape.setPoint(i, point);
		
#ifdef PRINT_DEBUG
		std::cout << point.x << " " << point.y << std::endl;
#endif
		
	}
}

Field::~Field()
{
}

sf::ConvexShape& Field::getShape()
{
	return mShape;
}

std::vector<GPSPoint>& Field::getCorners()
{
	return mCorners;
}

void Field::setPos(float const & x, float const y)
{
	mShape.setOrigin(sf::Vector2f(x, y));
}

void Field::printEdgeLengths()
{
	double distance = 0.0;
	for (size_t i = 0; i < mCorners.size(); i++)
	{
		if (i == mCorners.size() - 1)
			distance = calcDistance(mCorners[i].mLat, mCorners[i].mLong, mCorners[0].mLat, mCorners[0].mLong);
		else
			distance = calcDistance(mCorners[i].mLat, mCorners[i].mLong, mCorners[i + 1].mLat, mCorners[i + 1].mLong);
		std::cout << i << " -> " << i + 1 << " : " << distance * 1000 << " m" << std::endl;
	}
}

std::ostream & operator<<(std::ostream & out, Field & field)
{
	out << std::setprecision(15);
	std::vector<GPSPoint> points = field.getCorners();
	for (size_t i = 0; i < points.size(); i++)
	{
		if(i != 0)
			out << " -> ";
		out << points[i].mLat << " " << points[i].mLong;
	}
	out << std::endl;

	return out;
}

sf::Vector2f Field::mapToSFML(double const lat, double const lo)
{
	int const mult = 10000;
	sf::Vector2f mapped;
	mapped.x = (float)(lat - (int)lat) * mult;
	mapped.y = (float)(lo - (int)lo) * mult;

	return mapped;
}

//calculate haversine distance for linear distance (in km)
double Field::calcDistance(double lat1, double long1, double lat2, double long2)
{
	double dlong = (long2 - long1) * d2r;
	double dlat = (lat2 - lat1) * d2r;
	double a = pow(sin(dlat / 2.0), 2) + cos(lat1*d2r) * cos(lat2*d2r) * pow(sin(dlong / 2.0), 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	double dist = 6371.007 * c;

	return dist;
}

double Field::calcDistance(GPSPoint & p1, GPSPoint p2)
{
	return calcDistance(p1.mLat, p1.mLong, p2.mLat, p2.mLong);
}
