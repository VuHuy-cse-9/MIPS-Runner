#include "Register.h"

const char* Register::NAME_OF_REGISTER[] = { "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra", "$hi", "$lo", "$pc" };
const char* Register::DIGIT_OF_REGISTER[] = { "$0", "$1", "$2", "$3", "$4", "$5", "$6", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$16", "$17", "$18", "$19", "$20", "$21", "$22", "$23", "$24", "$25", "$26", "$27", "$28", "$29", "$30", "$31" };
const int Register::NAME_OF_REGISTER_SIZE = 32;
int Register::memoryOfRegister[35];

/*******************************************/
/***********Implement toInt method**********/
/*******************************************/
int size(const char* token) {
	int i = 0;
	while (token[i] != 0) i++;
	return i; // not include /0
}

int numb(const char* token, int length) {
	int* valueOfUnit = new int[length];
	for (int i = 0; i < length; ++i) {
		valueOfUnit[i] = 0;
	}
//I want to know how many unit of the literal
	int unit = 1;
	for( int i = 0; i < length - 1; ++i ) {
		unit = unit * 10;
	}
//I creat a integer by detect that digit and mulitiple 10^(level of unit)
	int result = 0;
	for (int i = 0; i < length; ++i) {
		while (valueOfUnit[i] != (int)(token[i] + 48)) {
			++valueOfUnit[i]; // now j would be same value as digit level i;
		}
		result += valueOfUnit[i] * unit;
		unit = unit / 10;
	} 
	delete[] valueOfUnit;
	return result;
}

int toInt(const char* token) {
	int length = size(token);
	int result;

	if(token[0] == '-'){  // negative number
		char* takePositiveNumber = new char[length - 1];
		for (int i = 1; i < length; ++i) {
			takePositiveNumber[i - 1] = token[i]; // My new char don't have substract's sign.
		}

		result = numb(takePositiveNumber, length) * -1;
		delete[] takePositiveNumber;
		takePositiveNumber = nullptr;
		return result;
	}
	else {//positive number
		result = numb(token, length);
		return result;
	}
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

	//Finish toInt
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
