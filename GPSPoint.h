#pragma once

#include <iostream>

class GPSPoint
{
public:
	GPSPoint();
	GPSPoint(double const la, double const lo);

	~GPSPoint();

	friend bool operator==(GPSPoint& a, GPSPoint& b);
	friend bool operator!=(GPSPoint& a, GPSPoint& b);
	friend std::ostream& operator<< (std::ostream& out, GPSPoint& point);

	double mLat;
	double mLong;
};

