#ifndef RESOURCEHOST_H
#define RESOURCEHOST_H

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <stringstream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


//#include 

#include "Resource.h"
const static char* const validIndexes[] ={
	"index.html",
	"index.htm"
}

class ResourceHost{
private:
	std::string baseDiskPath;

	std::unordered_map<std::string, std::string> mimeMap = {
	#define STR_PAIR(K,V) std::pair<std::string, std::string>(K,V)
	#include "MimeTypes.inc"
	};

	std::string lookupMimeType(std:: string ext);

	Resource* readFile(std::string path, struct stat );
	Resource* readDirectory(std::string path, struct stat );

	std::string generateList(std::string dirpath);
public:
	//ResourceHost();
	ResourceHost(std::string base);
	~ResourceHost();
	
	void putResource(Resource* res, bool writeToDisk);

	Resource* getResource(std::string url);
};

#endif 