#include "FilesystemWrapper.h"

FilesystemWrapper::FilesystemWrapper(){}

FilesystemWrapper::~FilesystemWrapper(){}

bool FilesystemWrapper::PathExists(const std::string &path){
	return boost::filesystem::exists(path);
}

bool FilesystemWrapper::PathIsDir(const std::string &path){
	return boost::filesystem::is_directory(path);
}