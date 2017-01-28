#pragma once
#define _USE_MATH_DEFINES

#include "misc.h"

/*
	This class calculates well trajectory by survey deviation data.
	Class uses for calculations balanced tangential method.
*/

class WellTrajectory
{
private:
	WellTrajectory();
	~WellTrajectory();
public:

	/* Calculate well trajectory by survey deviation data using balanced tangential method */
	static VecOfVecd calculate(VecOfVecd &surveyData);

	/* writes to file well trajectory in format: TVD North East */
	static bool writeFile(const std::string &path, VecOfVecd &wellTrajectory);
};

