#pragma once
#define MAX_ARGS 2

#include "misc.h"
#include "Parser.h"
//#include "

/*
	1) Computational geometry
		B) Area of the polygon

		Write a command line utility that inputs polygon data file and calculate area of polygon.

		File1: polygon data
		X1 Y1
		X2 Y2
		…

		Columns in files are separated with: colon, space or tab symbols (all separators are legal simultaneously).
*/

int main(int argc, char* argv[]){
	boost::filesystem::path p(argv[0]);

	std::string help = "Usage:\n\t" + p.filename().string() + " input_file\n\n";
	help += "positional arguments:\n";
	help += "\tinput_file\t\tPath to polygon vertices file\n";

	if (argc != MAX_ARGS) {
		std::cout << help;
		WAIT_USER
		return 1;
	}

	std::string polygonVertexFilePath = argv[1];
	if (boost::filesystem::is_directory(polygonVertexFilePath)){
		std::cout << "Error during reading file.. You're tried read directory, not a file!\n";
		WAIT_USER
		return 1;
	}

	if (!boost::filesystem::exists(polygonVertexFilePath)){
		boost::filesystem::path p(polygonVertexFilePath);
		std::cout << "Error during reading file " << p.filename() << " from " << p.parent_path() 
			<< ".. File is not exists!\n";
		WAIT_USER
		return 1;
	}

	WAIT_USER
	return 0;
}