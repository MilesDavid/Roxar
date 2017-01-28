#pragma once
#define MAX_ARGS 3

/*
	1) Computational geometry
		A) Point in polygon
		Write a command line utility that inputs two files:

		File1: polygon data
		X1 Y1
		X2 Y2
		…

		File2: points
		“Point1” X1 Y1
		“Point2” X2 Y2
		…

		Utility should outputs points inside the polygon.
		Columns in files are separated with: colon, space or tab symbols (all separators are legal simultaneously).
*/

#include "misc.h"
#include "Parser.h"
#include "GeometryWrapper.h"
#include "FilesystemWrapper.h"

int main(int argc, char* argv[]){
	Path p(argv[0]);

	std::string help = "Usage:\n\t" + p.filename().string() + " input_file\n\n";
	help += "positional arguments:\n";
	help += "\tinput_file\t\tPath to polygon vertices file\n";
	help += "\toutput_file\t\tPath to points file\n\n";

	if (argc != MAX_ARGS) {
		std::cout << help;
		WAIT_USER
		return 1;
	}

	std::string polygonVertexFilePath = argv[1];
	if (FilesystemWrapper::PathIsDir(polygonVertexFilePath)){
		std::cout << "Error during reading file.. You're tried read directory, not a file!\n";
		WAIT_USER
		return 1;
	}

	if (!FilesystemWrapper::PathExists(polygonVertexFilePath)){
		Path p(polygonVertexFilePath);
		std::cout << "Error during reading file " << p.filename() << " from " << p.parent_path() 
			<< ".. File is not exists!\n";
		WAIT_USER
		return 1;
	}

	std::string pointsFilePath = argv[2];
	if (FilesystemWrapper::PathIsDir(pointsFilePath)){
		std::cout << "Error during reading file.. You're tried read directory, not a file!\n";
		WAIT_USER
		return 1;
	}

	if (!FilesystemWrapper::PathExists(pointsFilePath)){
		Path p(pointsFilePath);
		std::cout << "Error during reading file " << p.filename() << " from " << p.parent_path() 
			<< ".. File is not exists!\n";
		WAIT_USER
		return 1;
	}

	VecPoint2D polygonVertices = Parser::parseFile(polygonVertexFilePath, "\t :");
	VecPoint2D points = Parser::parseFile(pointsFilePath, "\t :");

	VecPoint2D pointsInPolygon = GeometryWrapper::PointsInPolygon(&polygonVertices, &points);
	if (pointsInPolygon.size() != 0){
		printf_s("\nPoints in polygon:\n");
		GeometryWrapper::PrintPoints(&pointsInPolygon);
	}
	else
		printf_s("\nPolygon is not contains points..\n");

	WAIT_USER
	return 0;
}