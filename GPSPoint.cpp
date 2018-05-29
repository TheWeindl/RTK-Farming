#include "stdafx.h"
#include "GPSPoint.h"

using namespace std;

GPSPoint::GPSPoint()
{
	mLat = -1;
	mLong = -1;
}

GPSPoint::GPSPoint(double const la, double const lo)
{
	mLat = la;
	mLong = lo;
}


GPSPoint::~GPSPoint()
{
}

bool operator==(GPSPoint & a, GPSPoint & b)
{
	if (a.mLat == b.mLat && a.mLong == b.mLong)
		return true;
	else
		return false;
}

bool operator!=(GPSPoint & a, GPSPoint & b)
{
	return !(a == b);
}

std::ostream & operator<<(std::ostream & out, GPSPoint & point)
{
	out << point.mLat << " " << point.mLong;
	return out;
}
