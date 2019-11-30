#pragma once

#include <cstring>

class Register
{
private:
	static const char* NAME_OF_REGISTER[];
	static const char* DIGIT_OF_REGISTER[];
	static const int NAME_OF_REGISTER_SIZE;
	static int memoryOfRegister[];

	int* valuePtr;
	bool haveToDeleteMemory;
public:
	Register();
	Register(int);
	Register(const char*);
	~Register();

	Register operator+(Register);
	Register operator-(Register);
};



