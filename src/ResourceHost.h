class ResourceHost{
private:
	std::string baseDiskPath;

	std::unordered_map<std::string, std::string> mimeMap = {
	#define STR_PAIR(K,V) std::pair<std::string, std::string>(K,V)
	#include "MimeTypes.inc"
	};
public:
	void putResource(Resource* res, bool writeToDisk);

	Resource* getResource(std::string url);
};