#include "ByteBuffer.h"


ByteBuffer::ByteBuffer(unsigned int size){
	buf.reserve(size);
	clear();
}

ByteBuffer::ByteBuffer(byte* arr, unsigned int size){
	if(arr == NULL){
		buf.reserve(size);
		clear();
	}else{
		buf.reserve(size);
		clear();
		putBytes(arr,size);
	}

}
ByteBuffer::~ByteBuffer(){}


unsigned int ByteBuffer::bytesRemaining(){
	reutrn size()-rpos;
}

void ByteBuffer::clear(){
	
	rpos = 0;
	wpos = 0;
	buf.clear();
}


ByteBuffer* ByteBuffer::clone(){
	ByteBuffer* ret = new ByteBuffer(buf.size());

	for(unsigned int i = 0; i < buf.size(); i++){
		ret->put(i,(byte)get(i));
	}

	ret->setReadPos(0);
	ret->setReadPos(0);
	return ret;
}

bool ByteBuffer::equals(ByteBuffer* other){
	if(size() != other.size())
		return false;

	unsigned int len = size();
	for(unsigned int i = 0; i < len ; i++){
		if((byte)get(i) != (byte)other->get(i))
			return false;
	}
	return true;
}

void ByteBuffer::resize(unsigned int newSize){
	buf.resize(newSize);
	rpos = 0;
	wpos = 0;
}

unsigned int ByteBuffer::size(){
	return buf.size();
}

byte ByteBuffer::peek(){
	return read<byte>(rpos);
}

byte ByteBuffer::get(){
	return read<byte>();
}

byte ByteBuffer::get(unsigned int index){
	return read<byte>(index);
}

void ByteBuffer::getBytes(byte* otherbuf, unsinged int len){
	for(unsinged int i =0; i<len; i++)
		otherbuf[i] = read<byte>();
}

byte ByteBuffer::getChar(){
	return read<char>();
}

byte ByteBuffer::getChar(unsigned int index){
	return read<char>(index);
}
double ByteBuffer::getDouble(){
	return read<double>();
}
double ByteBuffer::getDouble(unsigned int index){
	return read<double>(index);
}


float ByteBuffer::getFloat(){
	return read<float>();
}
float ByteBuffer::getFloat(unsigned int index){
	return read<float>(index);
}

int ByteBuffer::getInt(){
	return read<int>();
}
int ByteBuffer::getInt(unsigned int index){
	return read<int>(index);
}

long ByteBuffer::getLong(){
	return read<long>();
}
long ByteBuffer::getLong(unsigned int index){
	return read<long>(index);
}

short ByteBuffer::getShort(){
	return read<short>();
}
short ByteBuffer::getShort(unsigned int index){
	return read<short>(index);
}

void ByteBuffer::put(ByteBuffer* src){
	int len = src->size();
	for(unsigned int i = 0; i<len; i++){
		append<byte>(src->get(i));
	}
}

void ByteBuffer::put(byte b){
	append<byte>(b);
}
void ByteBuffer::put(byte b, unsigned int index){
	insert<byte>(b,index);
}

void ByteBuffer::putBytes(byte* b, unsinged int len){
	for(unsigned int i = 0; i < len; i++){
		append<byte>(b[i]);
	}
}

void ByteBuffer::putBytes(byte* b, unsinged int len, unsinged int index){
	wpos = index;
	//putBytes(b,len);
	for(unsigned int i = 0; i < len; i++){
		append<byte>(b[i]);
	}
}

void ByteBuffer::putChar(char value){
	append<char>(value);
}

void ByteBuffer::putChar(char value, unsigned int index){
	insert<char>(value, index);
}

void ByteBuffer::putDouble(double value){
	append<double>(value);
}

void ByteBuffer::putDouble(double value, unsigned int index){
	insert<double>(value, index);
}

void ByteBuffer::putFloat(float value){
	append<float>(value);
}

void ByteBuffer::putFloat(float value , unsigned int index){
	insert<float>(value, index);
}

void ByteBuffer::putInt(int value){
	append<int>(value);
}
void ByteBuffer::putInt(int value, unsigned int index){
	insert<int>(value, index);
}

void ByteBuffer::putLong(long value){
	append<long>(value);
}

void ByteBuffer::putLong(long value, unsigned int index){
	insert<long>(value, index);
}

void ByteBuffer::putShort(short value){
	append<short>(value);
}

void ByteBuffer::putShort(short value, unsigned int index){
	insert<short>(value, index);
}

