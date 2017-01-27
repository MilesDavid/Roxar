#include "WellTrajectory.h"

WellTrajectory::WellTrajectory()
{
}

WellTrajectory::~WellTrajectory()
{
}

VecOfVecd WellTrajectory::parseFile(const std::string &path, const std::string &delims)
{
	std::fstream fs;
	fs.open(path, std::ios::in);

	std::string line;
	VecOfVecd survey;

	while (std::getline(fs, line)) {
		if (line[0] != '#') {
			std::vector<std::string> nums;
			boost::split(nums, line, boost::is_any_of(delims));

			std::vector<std::string>::iterator it = nums.begin();
			const int cols = 3;
			int count = 0;
			std::vector<double> tmp_survey;

			for (it; it != nums.end(); it++) {
				if (count == cols) break;
				try {
					double temp = std::stof(*it);
					tmp_survey.push_back(temp);
					count++;
				}
				catch (const std::exception&) {}
			}

			survey.push_back(tmp_survey);
		}
	}

	fs.close();

	return survey;
}

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

	std::vector<std::vector<double>> result;
	std::vector<std::vector<double>>::iterator it = surveyData.begin();

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

		std::vector<double> tmp;
		tmp.push_back(TVD2);
		tmp.push_back(North2);
		tmp.push_back(East2);

		result.push_back(tmp);
	}

	return result;
}

void WellTrajectory::writeFile(const std::string &path, VecOfVecd &wellTrajectory)
{
}



