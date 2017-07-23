class HTTPMessage: public ByteBuffer{
private:
	std::map<std::string, std::string>* headers;

protected:

	std::string version;

	byte* data;

public:

	virtual byte* create() = 0;

	virtual bool parse() = 0;
};