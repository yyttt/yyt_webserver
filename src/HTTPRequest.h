#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include "HTTPMessage.h"

class HTTPRequest:HTTPMessage{
private:
	int method;

	std::string requestURL;

protected:
	virtual void init();
public:
	HTTPRequest();
	HTTPRequest(std::string sData);
	HTTPRequest(byte* pData, unsigned int len);
	virtual ~HTTPRequest();
	 byte* create();
	 bool parse();

	int methodStrToInt(std::string name);
	std::string methodInToStr(unsigned int mid);

	void setMethod(int m){
		method = m;
	}

	int getMethod(){
		return method;
	}

	void setRequestURL(std::string url){
		requestURL = url;
	}

	void getRequestURL(){
		return requestURL;
	}


};
#endif