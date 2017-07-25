#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include "HTTPMessage.h" 


class HTTPResponse:public HTTPMessage{
private: 
	int status;
	std::string reason;

	void determineReasonstr();
	void determineStatusCode();

protected:
	virtual void init();

public:
	HTTPResponse();
	HTTPResponse(std::string sData);
	HTTPResponse(byte* pData, unsigned int len);
	virtual byte* create();

	virtual bool parse();

	void setSatus(int state){
		status = state;
		determineReasonstr();
	}

	std::string getReason(){
		return reason;
	}

};
#endif
