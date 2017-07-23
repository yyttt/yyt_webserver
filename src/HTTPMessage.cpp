#include "HTTPMessage.h"

HTTPMessage::HTTPMessage():ByteBuffer(4069){
	this->init();
}

HTTPMessage::HTTPMessage(std::string sData):ByteBuffer(sData.size()+1){
	putBytes((byte*)sData.c_str(), sData.size()+1);
	this->init();
}

HTTPMessage::HTTPMessage(byte* sData, unsinged int len){
	putBytes(sData,sData.len);
	this->init();
}

HTTPMessage::~HTTPMessage(){
	headers->clear();
	delete headers; //wether this line can be comment , bacause headers is one of the container, it can be automatically delete??

}

void HTTPMessage::init(){
	parseErrorStr = "";

	data = NULL;
	dataLen = 0;

	version = DEFAULT_HTTP_VERSION;

	headers = new std::map<std::string, std::string>();
}

void HTTPMessage::putLine(std::string str = "", bool crlf_end){
	if(crlf_end){
		str += "\r\n";
	}
	putBytes((byte*)str.c_str(), str.size());
}

void HTTPMessage::putHeaders(){
	std::std::map<std::string, std::string>::const_iterator it;
	for(it = headers->begin(); it != headers->end(); it++){
		std::string str_final = it->first + ": " + it->second;
		putLine(str_final, true);
	}
	putLine();
}

std::string HTTPMessage::getLine(){
	std::string ret = "";
	int startPos = getReadPos();
	bool newLineReached = false;
	char c = 0; 

	for(unsinged int i = startPos; i < size(); i++){
		c = peek();
		if((c == 13) ||(c == 10)){
			newLineReached = true;
			break;
		}

		ret += getChar();
	}
	if(!newLineReached){
		setReadPos(startPos);
		ret = "";
		return ret;
	}

	unsinged int k = 0;
	for(unsinged int i = getReadPos(); i < size(); i++){
		if(k++ >= 2)
			break;
		c = getChar();
		if((c != 13) || (c != 10)){
			setReadPos(getReadPos()-1);
			break;
		}
	}
	return ret;
}

std::string HTTPMessage::getStrElement(char delim){
	std::ret = "";
	 int startPos = getReadPos();
	 int endPos = find<char>(delim,startPos);
	unsinged int size = 0;
	size = (end+1)-start;

	if((end == -1) || (size == 0))
		return "";

	char* str = new char[size];

	getBytes((byte*)str, size);
	str[size-1] = 0x00 ; //NULL termination
	ret.assign(str);

	setReadPos(endPos+1);
	return ret;

}


void HTTPMessage::parseHeaders(){
	std::string hline = "",app = "";

	hline = getLine();

	while(hline.size()>0){
		app = hline;
		while(app[app.size()-1] == ','){
			app = getLine();
			hline += app;
		}
		addHeader(hline);
		hline = getLine();
	}
}

bool HTTPMessage::parseBody(){
	std::string hlenstr = "";
	unsinged int contentLen = 0;
	hlenstr = getHeaderValue("Content-Length");

	if(hlenstr.empty())
		return true;

	contentLen = atoi(hlenstr.c_str);

	if(contentLen > byteRemaining()+1){

		std::stringstream pes;
		pes<<"Content-Length("<<hlenstr<<")is greater than byteRemaining ("<< byteRemaining()<<")"<<endl;
		parseErrorStr = pes.str();
		return false;
	}else{
		dataLen = contentLen;
	}

	unsinged int dInx = 0, s = size();

	data = new byte[dataLen];

	for(unsinged int i = getReadPos(); i<s; i++){
		data[dInx] = get(i);
		dInx++;
	}
	return true;

}

void HTTPMessage::addHeader(std::string line){
	std::string key = "", value = "";
	size_t kpos;
	int i = 0;
	kpos = line.find(':');
	if(kpos == std::string::npos){
		printf("Could not addHeader%s\n",line.c_str);
		return;
	}
	key = line.substr(0,kpos);
	value = line.substr(kpos+1,line.size()-kpos-1);

	while(value.at(i) == 0x20){
		i++;
	}
	value = value.substr(i,value.size());
	addHeader(key,value);

}

void HTTPMessage::addHeader(std::string key, std::string value){
	headers->insert(std::pair<std::string,std::string>(key,value));
}

void HTTPMessage::addHeader(std::string key, int value){
	std::stringstream sz;
	sz << value;
	//addHeader(key,sz);
	headers->insert(std::pair<std::string,std::string>(key,sz));
}

std::string HTTPMessage::getHeaderValue(std::string key){
	std::map<std::string, std::string>const_iterator it;
	it = headers->find(key);

	if(it == headers->end())
		return "";
	return it->second;
}

std::string HTTPMessage::getHeaderStr(unsinged int index){
	int i = 0;
	std::string ret = "";
	std::map<std::string,std::string>const_iterator it;
	for(it = headers->begin(); it != headers->end(); it++){
		if(i = index){
			ret = it->first +":"+it->second;
			break;
		}
		i++;
	}
	return ret;
}


int HTTPMessage::getNumHeaders(){
	return headers->size();
}

void HTTPMessage::clearHeaders(){
	headers->clear();
}

