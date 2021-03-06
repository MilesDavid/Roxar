#include "WellTrajectory.h"

#include <cmath>
#include <cstdio>

WellTrajectory::WellTrajectory(){}

WellTrajectory::~WellTrajectory(){}

VecOfVecd WellTrajectory::calculate(VecOfVecd &surveyData)
{
	/*
		Balanced tangential method
		North = SUM(MD2 - MD1) * ((Sin WD1 * Cos HAZ1 + Sin WD2 * Cos HAZ2) / 2)
		East = SUM(MD2 - MD1) * ((Sin WD1 * Sin HAZ1 + Sin WD2 * Sin HAZ2) / 2)
		TVD = SUM((MD2 - MD1) * (Cos WD2 + Cos WD1) / 2)
	*/

	double MD1 = 0.0, WD1 = 0.0, AZ1 = 0.0;
	double North1 = 0.0, East1 = 0.0, TVD1 = 0.0;

	VecOfVecd result;
	VecOfVecd::iterator it = surveyData.begin();

	for (it; it != surveyData.end(); it++) {
		double MD2 = (*it)[0], WD2 = (*it)[1], AZ2 = (*it)[2];
		double dMD = MD2 - MD1;
		double radFix = M_PI / 180;

		double radWD1 = WD1 * radFix, radWD2 = WD2 * radFix;
		double radAZ1 = AZ1 * radFix, radWAZ2 = AZ2 * radFix;

		double sinWD1 = sin(radWD1), cosWD1 = cos(radWD1);
		double sinWD2 = sin(radWD2), cosWD2 = cos(radWD2);
		double sinAZ1 = sin(radAZ1), cosAZ1 = cos(radAZ1);
		double sinAZ2 = sin(radWAZ2), cosAZ2 = cos(radWAZ2);

		double North2 = dMD * (sinWD1 * cosAZ1 + sinWD2 * cosAZ2) / 2.0 + North1;
		double East2 = dMD * (sinWD1 * sinAZ1 + sinWD2 * sinAZ2) / 2.0 + East1;
		double TVD2 = dMD * (cosWD1 + cosWD2) / 2.0 + TVD1;

		MD1 = MD2; WD1 = WD2; AZ1 = AZ2;
		North1 = North2; East1 = East2; TVD1 = TVD2;

		Vecd tmp;
		tmp.push_back(TVD2);
		tmp.push_back(North2);
		tmp.push_back(East2);

		result.push_back(tmp);
	}

	return result;
}

bool WellTrajectory::writeFile(const std::string &path, VecOfVecd &wellTrajectory)
{
	if (wellTrajectory.size() == 0)
		return false;

	FILE* fp = NULL;
	errno_t err = fopen_s(&fp, path.c_str(), "w");

	if (err != 0)
		return false;

	fprintf_s(fp, "#%+9.10s%+10.10s%+10.10s\n", "TVD", "North", "East");
	VecOfVecd::iterator it = wellTrajectory.begin();
	for (it; it != wellTrajectory.end(); it++)
		fprintf_s(fp, "%10.2f%10.2f%10.2f\n", (*it)[0], (*it)[1], (*it)[2]);

	fclose(fp);

	return true;
}



