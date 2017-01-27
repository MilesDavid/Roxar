#pragma once
#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>
#include <fstream>
#include <string>

#include <boost\algorithm\string.hpp>

typedef std::vector<std::vector<double>> VecOfVecd;

/*
	This class calculates well trajectory by survey deviation data.
	Class uses for calculations balanced tangential method.
*/

class WellTrajectory
{
public:
	WellTrajectory();
	~WellTrajectory();

	static VecOfVecd parseFile(const std::string &path, const std::string &delims="\t :");
	static VecOfVecd calculate(VecOfVecd &surveyData);
	static void writeFile(const std::string &path, VecOfVecd &wellTrajectory);
};

