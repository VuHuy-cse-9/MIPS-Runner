#include "Register.h"

using namespace std;

const char* Register::NAME_OF_REGISTER[] = { "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra", "$hi", "$lo", "$pc" };
const char* Register::DIGIT_OF_REGISTER[] = { "$0", "$1", "$2", "$3", "$4", "$5", "$6", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$16", "$17", "$18", "$19", "$20", "$21", "$22", "$23", "$24", "$25", "$26", "$27", "$28", "$29", "$30", "$31" };
const int Register::NAME_OF_REGISTER_SIZE = 32;
int Register::memoryOfRegister[35];

/*******************************************/
/***********Implement toInt method**********/
/*******************************************/

int toInt(const char* token) {
	int length = strlen(token) - 1; // eliminate \0.
	int result = 0;
	int begin = 0;
	int sign = 1;
	if (token[0] == '-') {
		begin = 1;
		sign = -1;
	}
	for (int i = begin; i < length; ++i) {
		result = result * 10 + (token[i] - '0');
	}
	return result * sign;

}
/****************************************************************/

Register::Register() {
	this->valuePtr = nullptr;
	this->haveToDeleteMemory = false;
}

// constructor for storing data not in memoryOfRegister
Register::Register(int _value) {
	this->valuePtr = new int;
	*(this->valuePtr) = _value;
	this->haveToDeleteMemory = true;
}

Register::Register(const char* token) {
	for (int i = 0; i < NAME_OF_REGISTER_SIZE; ++i) {
		if (strcmp(NAME_OF_REGISTER[i], token) == 0 || strcmp(DIGIT_OF_REGISTER[i], token) == 0) {
			this->valuePtr = memoryOfRegister + i;
			this->haveToDeleteMemory = false;
			return;
		}
	}
	int value = toInt(token);
	this->valuePtr = new int;
	*valuePtr = value;
	this->haveToDeleteMemory = true;
}

Register::~Register() {
	if (this->haveToDeleteMemory)
		delete this->valuePtr;
}

Register Register::operator+(Register operand) {
	int sum = *(this->valuePtr) + *operand.valuePtr;
	Register result(sum);
	return result;
}

Register Register::operator-(Register operand) {
	int dif = *(this->valuePtr) - *(operand.valuePtr);
	Register result(dif);
	return result;
}

Register Register::operator&(Register operand) {
	int a = *(this->valuePtr) & *(operand.valuePtr);
	Register result(a);
	return result;
}

Register Register::operator|(Register operand) {
	int a = *(this->valuePtr) | *(operand.valuePtr);
	Register result(a);
	return result;
}


