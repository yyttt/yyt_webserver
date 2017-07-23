class HTTPResponse:public HTTPMessage{
private: 
	int status;
	std::string reason;

protected:
	virtual void init();

public:
	virtual byte* create();

	virtual bool parse();
};