#ifndef _BYTEBUFFER_H_
#define _BYTEBUFFER_H_

#define DEFAULT_SIZE 4096

#include <cstdlib>
#include <cstring>
#include <vector>

typedef unsigned char byte;

class ByteBuffer{

private:
	unsigned int rpos,wpos;

	std::vector<byte> buf;

	template<typename T>
	T read(unsigned int index) const{
		if(index + sizeof(T) <= buf.size())
			return *((T*)&buf[index]);
		return 0;
	}

	template<typename T>
	T read(){
		T data = read<T>(rpos);
		rpos += sizeof(T);
		return data;
	}

	template<typename T>
	void append( T data){
		unsigned int s = sizeof(data);

		if(size() < (wpos +s))
			buf.resize(wpos+s);
		memcpy(&buf[wpod],(byte*)data,s);
		wpos += s;
	} 

	template<typename T>
	void insert(T data, unsigned int index){
		if(index + sizeof(data) > size())
			return;
		memcpy(&buf[index],(byte*)data,sizeof(data));
		wpos = index + sizeof(data);
	}



public:

	ByteBuffer(unsigned int size = DEFAULT_SIZE);
	ByteBuffer(byte* arr, unsigned int size);
	virtual ~ByteBuffer();


	unsigned int bytesRemaining();

	void clear();

	ByteBuffer* clone();

	bool equals(ByteBuffer* other);

	void resize(unsigned int newSize);

	unsigned int size();//存储空间大小

	template<typename T>
	int find(T key, unsinged int start = 0){
		int ret = -1;
		unsigned int len = buf.size();
		for(unsigned int i = start; i < len; i++){
			T data = read<T>(i);
			if((key != 0) && (data == 0))  //if key == 0 and data == 0 ,a little bug 
				break;
			if(data == key)
			{
				ret = i;
				break;
			}
		}
		return ret;
	}

	// 读取队列头部的数据但不移动rpos
	byte peek();
	// 读取队列头部的数据同时移动rpos
	byte get();
	// 读取指定位置的数据
	byte get(unsigned int index);
	// 读取队列头部指定长度的数据到buf中
	void getBytes(byte* buf, unsigned int len);

	// 读取指定数据类型的元素：char，double，float，int，long，short
	char getChar();
	char getChar(unsigned int index);

	double getDouble();
	double getDouble(unsigned int index);

	float getFloat();
	float getFloat(unsigned int index);

	int getInt();
	int getInt(unsigned int index);

	long getLong();
	long getLong(unsigned int index);

	short getShort();
	short getShort(unsigned int index);


	void put(ByteBuffer* src);

	void put(byte b);

	void putBytes(byte* b, unsinged int len);

	void putBytes(byte* b, unsinged int len , unsinged int index);

	void putChar(char value);
	void putChar(char value, unsigned int index);

	void putDouble(double value);
	void putDouble(double value, unsigned int inex);

	void putFloat(float value);
	void putFloat(float value, unsigned int index);

	void putInt(int value);
	void putInt(int value, unsigned int index);

	void putLong(long value);
	void putLong(long value, unsigned int index);

	void putShort(short value);
	void putShort(short value, unsigned int index);

	void setReadPos(unsigned int r){
		rpos = r;
	}

	void setWritePos(unsigned int w){
		wpos = w;
	}

	unsigned int getReadPos(){
		return rpos;
	}

	unsigned int getWritePos(){
		return wpos;
	}

};
#endif