#pragma once
#include "misc.h"

/*
	This class parses text files with numeric data.
*/

class Parser{
private:
	Parser();
	~Parser();
public:
	/* Parse file to cols-dimensional vectors excluding comment strings begins #-symbol */
	static VecOfVecd parseFile(const std::string &path, const std::string &delims, const int cols);

	/* Parse file to 2d vectors (points) excluding comment strings begins #-symbol */
	static VecPoint2D Parser::parseFile(const std::string &path, const std::string &delims);
};