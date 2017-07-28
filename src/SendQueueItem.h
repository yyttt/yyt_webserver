#ifndef SENDQUEUEITEM_H
#define SENDQUEUEITEM_H

//#include <cstdlib>

typedef unsigned char byte

class SendQueueItem{
private:
	byte* sendData;
	unsigned int sendSize;
	unsigned int sendOffset;
	bool disconnect;

public:
	SendQueueItem(){
		sendData = NULL;
		sendSize = 0;
		sendOffset = 0;
		disconnect = true;
	}
	SendQueueItem(byte *sData,unsigned int size, bool dc){
		sendData = sData;
		sendSize = size;
		sendOffset = 0;
		disconnect = dc;
	};

	~SendQueueItem(){
		if(sendData != NULL){
			delete[] sendData;
			sendData = NULL;
		}
	}

	byte *getData(){
		return sendData;
	}

	unsigned int getSendSize(){
		return sendSize;
	}

	unsigned int getOffset(){
		return sendOffset;
	}

	void setSendOffset(unsigned int offset){
		sendOffset = offset;
	}

	bool getDisconnect(){
		return disconnect;
	}

};

#endif