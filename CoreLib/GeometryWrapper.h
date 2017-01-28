#pragma once
#include "misc.h"

/*
	This class wrap some functions from boost geometry.
*/

class GeometryWrapper
{
private:
	GeometryWrapper();
	~GeometryWrapper();
public:

	/* Returns points contains in polygon */
	static VecPoint2D PointsInPolygon(VecPoint2D* polygonVertices, VecPoint2D* points);
	
	/* Calculates polygon's area */
	static double PolygonArea(VecPoint2D* polygonVertices);

	/* Print points to console */
	static void PrintPoints(VecPoint2D* points);
};

