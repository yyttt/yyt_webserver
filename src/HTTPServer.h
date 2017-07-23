
class HTTPServer{
private:
	int listenPort;//listening port
	int listenSocket; //listening socket

	struct sockaddr_in serverAddr;

	int kqfd; //kqueue fd

	struct kevent evList[QUEUE_SIZE];

	std::unordered_map<int, Client*>clientMap; //strore matched client and fd;

	std::vector<ResourceHost*>hostList;

	std::unordered_map<std::string, ResourceHost*>vhosts;

public:


	void acceptConnection();//dealing with client connections

	void disconnectClient(Client* cl,bool mapErase = true);

	void readClient(Client* cl, int data_len);

	bool writeClient(Client* cl, int avail_bytes);


	void handleRequest(Client* cl, HTTPRequest* req);

	void handleGet(Client* cl, HTTPRequest* req, ResourceHost* resHosst);

	void handleOptions(Client* cl, HTTPRequest* req);


	void sendStatusResponse(Client* cl, int status, std::string msg ="");

	void sendResponse(Client* cl, HTTPResponse* resp, bool disconnect);


	bool start(int port);

	void stop();


	void process();






};