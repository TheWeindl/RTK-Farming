#pragma once

//Temporary class for representing the tool/tractor with its parameters
class Tool
{
public:
	Tool();
	~Tool();

	enum eOrientation {
		eNorth,
		eEast
	};

	double toolWidth = 6.0;						//Tool width of the tractor in meters
	eOrientation drivingDirection = eNorth;		//Direction the driving line will be parallel to
};

