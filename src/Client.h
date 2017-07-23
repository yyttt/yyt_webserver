class Client{
	int socketDesc;
	sockaddr_in clientAddr;
	std::queue<SendQueueItem*>sendQueue;

public:

	void addToSendQueue(SendQueueItem* item);

	unsigned int sendQueueSize();

	SendQueueItem* nextInSendQueue();

	void dequeueFromSendQueue();

	void clearSendQueue();
};