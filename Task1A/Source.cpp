#define _USE_MATH_DEFINES
#define MAX_ARGS 3

#include <iostream>

#include "WellTrajectory.h"

int main(int argc, char* argv[]) {
	std::string programPath = argv[0];
	std::vector<std::string> lines;

	boost::split(lines, programPath, boost::is_any_of("\\"));
	std::string help = "Usage:\n\t" + lines.back() + " input_file output_file\n\n";
	help += ""

	if (argc != MAX_ARGS) {
		std::cout << help;
		return 1;
	}

	std::string inputPath = argv[1];
	std::string outputPath = argv[2];

	VecOfVecd data = WellTrajectory::parseFile(inputPath);
	VecOfVecd wellTrajectory = WellTrajectory::calculate(data);
	WellTrajectory::writeFile(outputPath, wellTrajectory);

	std::vector<std::vector<double>>::iterator it = wellTrajectory.begin();
	for (it; it != wellTrajectory.end(); it++) {
		std::vector<double> tmp = *it;
		std::vector<double>::iterator itd = tmp.begin();

		for (itd; itd != tmp.end(); itd++) {
			std::cout << (*itd) << "\t";
		}
		std::cout << std::endl;
	}

	system("pause");
	return 0;
}