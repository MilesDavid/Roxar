#pragma once
#define _USE_MATH_DEFINES
#define MAX_ARGS 3

#include "misc.h"
#include "Parser.h"
#include "FilesystemWrapper.h"
#include "WellTrajectory.h"

/*
	2) Geological data processing
		A) Make well trajectory from deviation survey data.

		Write a command line utility that inputs deviation survey data (text file) with structure:
		Column 1 -MD (measured depth)
		Column 2 -Angle
		Column 3 –Azimuth

		Columns are separated with: colon, space or tab symbols (all separators are legal simultaneously).

		Example:
			10	0.2	140
            20	0.2	141
            30	0.2	142
            40	0.2	143
            50	0.2	144
            60	0.3	145
            70	0.4	146
            80	1	147
            90	1.1	148

		Utility should calculate parameters:
		- Offset in East direction (DX)
		- Offset in North direction (DY)
		- True vertical depth (TVD) from wellhead.

		Utility should produce trajectory text file:
		Column 1 -TVD
		Column 2 -DX
		Column 3 –DY
*/

int main(int argc, char* argv[]) {
	Path p(argv[0]);

	std::string help = "Usage:\n\t" + p.filename().string() + " input_file output_file\n\n";
	help += "positional arguments:\n";
	help += "\tinput_file\t\tPath to input file with survey deviation data\n";
	help += "\toutput_file\t\tPath to output file with well trajectory\n\n";

	if (argc != MAX_ARGS) {
		std::cout << help;
		WAIT_USER
		return 1;
	}

	std::string inputPath = argv[1];
	std::string outputPath = argv[2];

	if (FilesystemWrapper::PathIsDir(inputPath)){
		std::cout << "Error during reading file.. You're tried read directory, not a file!\n";
		WAIT_USER
		return 1;
	}

	if (!FilesystemWrapper::PathExists(inputPath)){
		Path p(inputPath);
		std::cout << "Error during reading file " << p.filename() << " from " << p.parent_path() 
			<< ".. File is not exists!\n";
		WAIT_USER
		return 1;
	}

	VecOfVecd data = Parser::parseFile(inputPath, "\t :", 3);
	VecOfVecd wellTrajectory = WellTrajectory::calculate(data);

	if (!WellTrajectory::writeFile(outputPath, wellTrajectory)){
		Path p(outputPath);

		if (FilesystemWrapper::PathIsDir(outputPath)){
			std::cout << "Error during writing to file.. You're tried write to directory, not a file!\n";
			WAIT_USER
			return 1;
		}

		std::cout << "Error during writing to file " << p.filename() << ".. "
			<< "Maybe, your user haven't permissions to write in " << p.parent_path() << "?\n";
	}

	WAIT_USER
	return 0;
}