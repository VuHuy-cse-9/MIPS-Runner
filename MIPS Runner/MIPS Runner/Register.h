#pragma once

#include <iostream>
#include <cstring>

#include "LabelManager.h"

/*
Register store:
	real memory
		a real register address.
		a memory address.

	program created memory
		a label. -> address of register $pc.
		a constant. -> create a new integer, then store its adress.
*/ 

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
	Register(void*);
	Register(const Register&);
	~Register();

	Register& operator=(const Register&) &;
	Register operator+(const Register&) const &;
	Register operator-(const Register&) const &;
	Register operator*(const Register&) const &;
	Register operator&(const Register&) const &;
	Register operator|(const Register&) const &;
	Register operator<<(const Register&) const &;
	Register operator>>(const Register&) const &;
	Register addUnsigned(const Register&) const &;
	Register subtractUnsigned(const Register&) const &;
	bool operator>(const Register&) const &;
	bool operator==(const Register&) const &;
	bool operator!=(const Register&) const &;
	bool operator>=(const Register&) const &;
	bool operator<(const Register&) const &;
	bool operator<=(const Register&) const &;
	
	int getValue();
	int advance(int);
};



