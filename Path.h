#pragma once

#include <vector>
#include "GPSPoint.h"
#include "Field.h"

class Path
{
public:
	Path();
	~Path();

	void calcPath(Field * pField);

private:
	std::vector<GPSPoint> mWayPoints;
};

