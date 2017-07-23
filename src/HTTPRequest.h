class HTTPRequest:HTTPMessage{
private:
	int method;

	std::string requestURL;

protected:
	virtual void init();
public:
	virtual byte* create();
	virtual bool parse();

	int methodStrToInt(std::string name);
	std::string methodInToStr(unsigned int mid);
};