#define _USE_MATH_DEFINES
#define MAX_ARGS 3

#define WAIT_USER char ch; std::cout << "Press any key, then Enter key.."; std::cin >> ch;

#include <iostream>

#include <boost/filesystem.hpp>

#include "WellTrajectory.h"

int main(int argc, char* argv[]) {
	boost::filesystem::path p(argv[0]);

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

	if (boost::filesystem::is_directory(inputPath)){
		std::cout << "Error during reading file.. You're tried read directory, not a file!\n";
		return 1;
	}

	if (!boost::filesystem::exists(inputPath)){
		boost::filesystem::path p(inputPath);
		std::cout << "Error during reading file " << p.filename() << " from " << p.parent_path() 
			<< ".. File is not exists!";
		WAIT_USER
		return 1;
	}

	VecOfVecd data = WellTrajectory::parseFile(inputPath);
	VecOfVecd wellTrajectory = WellTrajectory::calculate(data);

	if (!WellTrajectory::writeFile(outputPath, wellTrajectory)){
		boost::filesystem::path p(outputPath);

		if (boost::filesystem::is_directory(outputPath)){
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