#pragma once

#include <vector>
#include "sfml/GPSPoint.h"
#include "sfml/Field.h"

class Path
{
public:
	Path();
	~Path();

	void calcPath(Field * pField);

private:
	std::vector<GPSPoint> mWayPoints;
};

