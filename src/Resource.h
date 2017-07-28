#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
class Resource{
private:
	//
	byte* data; //resource
	unsigned int size;//resource size

	std::string mimeType;//resource type
	std::string location;

	bool directory;
	
public:
	Resource(std::string loc, bool dirc = false);

	~Resource();

	void setMimeType(std::string mt){
		mimeType = mt;
	}

	std::string getMimeType(){
		return mimeType;
	}

	void setData(byte *d, unsigned int len){
		data = d;
		size = len;
	};

	byte* getData(){
		return data;
	}

	void setLocation(std::string loc){
		location = loc;
	}

	std::string getLocation(){
		return location;
	}

	bool setDirectory(bool dirc){
		directory = dirc;
	}

	std::string getExtension(){
		std::string ret ="";
		auto ext_pos = location.find_last_of(".");
		if(ext_pos != std::string.npos)
			 ret = location.substr(ext_pos+1);
		return ret;
	}

};
#endif