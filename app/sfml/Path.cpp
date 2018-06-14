//#include "stdafx.h"
#include "Path.h"

using namespace std;

Path::Path()
{
}


Path::~Path()
{
}

void Path::calcPath(Field * pField)
{
	if (pField == nullptr)
	{
		return;
	}

	//Get corners of the field
	vector<GPSPoint> corners = pField->getCorners();

	//TODO: First drive in straight lines 



	//TODO: Drive around the outside edges twice to cover up the edges an turning areas
}
