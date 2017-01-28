#include "Parser.h"

#include <fstream>

#include <boost/algorithm/string.hpp>

Parser::Parser(){}

Parser::~Parser(){}

VecOfVecd Parser::parseFile(const std::string &path, const std::string &delims, const int cols)
{
	std::fstream fs;
	fs.open(path, std::ios::in);

	std::string line;
	VecOfVecd data;

	while (std::getline(fs, line)) {
		if (line[0] != '#') {
			Vecs nums;
			boost::split(nums, line, boost::is_any_of(delims));

			Vecs::iterator it = nums.begin();
			int count = 0;
			Vecd tmp;

			for (it; it != nums.end(); it++) {
				if (count == cols) break;
				try {
					double temp = std::stof(*it);
					tmp.push_back(temp);
					count++;
				}
				catch (const std::exception&) {}
			}

			if (tmp.size() == cols)
				data.push_back(tmp);
		}
	}

	fs.close();

	return data;
}

VecPoint2D Parser::parseFile(const std::string &path, const std::string &delims)
{
	std::fstream fs;
	fs.open(path, std::ios::in);

	std::string line;
	VecPoint2D points;

	while (std::getline(fs, line)) {
		if (line[0] != '#') {
			Vecs nums;
			boost::split(nums, line, boost::is_any_of(delims));

			Vecs::iterator it = nums.begin();
			int count = 0;
			Vecd tmp;

			for (it; it != nums.end(); it++) {
				double x, y;
				try {
					double temp = std::stof(*it);
					if (count == 0){
						x = temp;
					}
					else if(count = 1){
						y = temp;
						points.push_back(Point2D(x, y));
						break;
					}
					count++;
				}
				catch (const std::exception&) {}
			}
		}
	}

	fs.close();

	return points;
}
