#pragma once

#include <iostream>
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
	Register(const Register&);
	void getRegister();
	~Register();

	Register& operator=(const Register&) &;
	Register operator+(const Register&) const &;
	Register operator-(const Register&) const &;
	Register operator&(const Register&) const &;
	Register operator|(const Register&) const &;
	Register operator<<(const Register&) const &;
	Register operator>>(const Register&) const &;
	Register addu(const Register&) const &;// addu
	Register subu(const Register&) const &;//subu
	Register operator*(const Register&) const &;
	Register operator<(const Register&) const &;
};



