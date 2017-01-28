#include "GeometryWrapper.h"

GeometryWrapper::GeometryWrapper(void){}

GeometryWrapper::~GeometryWrapper(void){}

VecPoint2D GeometryWrapper::PointsInPolygon(VecPoint2D* polygonVertices, VecPoint2D* points){
	Polygon2D polygon;
	boost::geometry::assign_points(polygon, *polygonVertices);

	VecPoint2D pointsInPolygon;
	for (VecPoint2D::iterator it = points->begin(); it != points->end(); it++)
		if (boost::geometry::within(*it, polygon))
			pointsInPolygon.push_back(*it);

	return pointsInPolygon;
}

double GeometryWrapper::PolygonArea(VecPoint2D* polygonVertices){
	Polygon2D polygon;
	boost::geometry::assign_points(polygon, *polygonVertices);
	return boost::geometry::area(polygon);
}

void GeometryWrapper::PrintPoints(VecPoint2D* points){
	for (VecPoint2D::iterator it = points->begin(); it != points->end(); it++)
		printf_s("Point(%10.2f,%10.2f)\n", (*it).x(), (*it).y());
}
