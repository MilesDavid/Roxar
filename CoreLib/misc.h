#pragma once

/*
	This file contains some type definitions and macroses using in this solution.
*/

#include <vector>
#include <iostream>
#include <string>

#include <boost/filesystem.hpp>

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

#define WAIT_USER char ch; std::cout << "\nPress any key, then Enter key..\n"; std::cin >> ch;

typedef std::vector<std::string> Vecs;
typedef std::vector<double> Vecd;
typedef std::vector<std::vector<double>> VecOfVecd;

typedef boost::geometry::model::d2::point_xy<double> Point2D;
typedef std::vector<Point2D> VecPoint2D;
typedef boost::geometry::model::polygon<Point2D> Polygon2D;

typedef boost::filesystem::path Path;