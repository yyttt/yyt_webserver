#include "Resource.h"

Resource::Resource(std::string loc, bool dir ){
	location = loc;
	directory = dir;
	mimeType = "";
	data = NULL:
	size = 0;
}

Resource::~Resource(){
	if(data != NULL){
		delete[] data;
		data = NULL:
	}

}
