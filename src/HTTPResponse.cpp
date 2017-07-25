#include "HTTPResonpse.h"

HTTPResonpse::HTTPResonpse():HTTPMesaage(){
	this->init();
}

HTTPResonpse::HTTPResonpse(std::string sData):HTTPMesaage(sData){
	this->init();
}

HTTPResonpse::HTTPResonpse(byte* pData, unsigned int len):HTTPMesaage(pData,len){
	this->init();
}

void HTTPResonpse::init(){
	status = 0;
	reason ="";
}

void HTTPResonpse::determineReasonstr(){
	switch(status){
		case Status[CONTINUE]:
			reason = "Continue";
			break;
		case Status[OK]:
			reason = "OK";
			break;
		case Status[BAD_REQUESR]:
			reason = "Bad_Request";
			break;
		case Status[NOT_FOUND]:
			reason = "Not_Found";
			break;
		case Status[SERVER_ERROR]:
			reson = "Server error"
			break;
		case Status[NOT_IMPLEMENT]:
			reason = "not implement";
			break;
		default:
			break;
	}
}
void HTTPResonpse::determineStatusCode(){
	if(reason.find("Continue") != std::string::npos)
		status = Status[CONTINUE];
	else if(reason.find("OK") != std::string::npos)
		status = Status[OK];
	else if(reason.find("Bad_Request")!= std::string::npos)
		status = Status[BAD_REQUESR];
	else if(reason.find("Not_Found") != std::string::npos)
		status = Status[NOT_FOUND];
	else if(reason.find("Server error")!= std::string::npos)
		status = Status[SERVER_ERROR];
	else if(reason.find("not implement")!= std::string::npos)
		status = Status[NOT_IMPLEMENT];
	else{

	}
}

byte* HTTPResonpse::create(){
	clear();
	std::stringstream sline;
	sline<<version<<" "<<status<<" "<<reason;
	putline(sline.str());

	putHeaders();

	if((data!=NULL) && dataLen>0){
		putBytes(data,dataLen);
	}

	byte*createRetData = new byte[size()];
	setReadPos(0);
	getBytes(createRetData,size());
	return createRetData;
}


bool HTTPResonpse::parse(){
	std::string statusstr;
	version = getStrElement();
	statusstr = getStrElement();
	determineStatusCode();
	reason = getLine();

	parseHeaders();
	if(!parseBody())
		return false;
	return true;

}