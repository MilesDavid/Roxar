#pragma once
#include "misc.h"

class FilesystemWrapper
{
private:
	FilesystemWrapper();
	~FilesystemWrapper();
public:
	static bool PathExists(const std::string &path);
	static bool PathIsDir(const std::string &path);
};

