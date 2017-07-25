#include "HTTPRequest.h"

HTTPRequest::HTTPRequest():HTTPMessage(){
	this->init();
}

HTTPRequest::HTTPRequest(std::string sData):HTTPMessage(sData){
	this->init();
}

HTTPRequest::HTTPRequest(byte* pData, unsigned int len):HTTPMessage(pData,len){
	this->init();
}

HTTPRequest::~HTTPRequest(){}

void init(){
	method = 0;
	requestURL = "";
}

int HTTPRequest::methodStrToInt(std::string name){
	if(name.empty() || name.size()>=10)
		return -1;
	int ret = -1
	for(unsigned int i = 0; i < NUM_METHODS; i++){
		if(strcmp(requestMethodStr[i],name.c_str()) == 0)
		{
			ret = i;
			break;
		}
	}
	return ret;
}


std::string HTTPRequest::methodIntToStr(unsigned int i){
	if(i >= NUM_METHODS)
		return "";
	return requestMethodStr[i];

}

 byte* HTTPRequest::create(){
 	clear();

 	std::string mstr = "";
 	mstr = methodIntToStr(method);

 	if(mstr.empty()){
 		printf("could not create HTTPRequest, unknown method :%i\n",method);
 		return NULL;
 	}
 	putLine(mstr + " " + requestURL + " " + version);
 	putHeaders();

 	if((data!=NULL) && dataLen >0){
 		putBytes(data,dataLen);
 	}

 	byte *createRetData = new byte[size()];
 	setReadPos(0);

 	getBytes(createRetData,size());

 	return createRetData;


}

void HTTPRequest::parse(){
	std::string initial = "", methodName = "";
	
	methodName = getStrElement();
	requestURL = getStrElement();
	version = getLine();

	method = methodStrToInt(methodName);
	if(method = -1)
	{
		parseErrorStr = "Invalid method:" + methodName;
		return false;
	}

	parseHeaders();

	if(method != POST && method != PUT)
		return true;
	if(!parseBody())
		return false;
	return true;


};