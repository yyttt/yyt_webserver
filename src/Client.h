#ifndef CLIENT_H
#define CLIENT_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include <queue>

#include "SendQueueItem.h"

class Client{
	//connected socket
	int socketDesc;
	sockaddr_in clientAddr;
	std::queue<SendQueueItem*>sendQueue;

public:
	Client(int fd, sockaddr_in clientaddr);
	~Client();

	in getSocket(){
		return socketDesc;
	}

	sockaddr_in getClientAddr(){
		return clientAddr;
	}

	char *getClientIP(){
		inet_ntoal(clientAddr.sin_addr);
	} 

	void addToSendQueue(SendQueueItem* item);

	unsigned int sendQueueSize();

	SendQueueItem* nextInSendQueue();

	void dequeueFromSendQueue();

	void clearSendQueue();
};
#endif