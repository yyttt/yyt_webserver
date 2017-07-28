#include "Client.h"

Client::Client(int fd, sockAddr_in clientaddr){
	socketDesc = fd;
	clientAddr = clientaddr;

}

Client::~Client(){
	clearSendQueue();
}

void Client::addToSendQueue(SendQueueItem *item){
	sendQueue.push(item);
}
unsigned int Client::sendQueueSize(){
	return sendQueue.size();
}

SendQueueItem *Client::nextInSendQueue(){
	if(!sendQueue.empty())
		return SendQueueItem.front();
	else 
		return NULL;
}

void dequeueFromSendQueue(){
	SendQueueItem *Item = nextInSendQueue();
	if(Item != NULL){
		delete Item;
		//Item = NULL;
	}
	SendQueue.pop();
}

void clearSendQueue(){
	while(!SendQueue.empty()){
		//dequeueFromSendQueue();
		delete SendQueue.front();
		SendQueue.pop();
	}
}