#include "Register.h"

using namespace std;

const char* Register::NAME_OF_REGISTER[] = { "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra", "$hi", "$lo", "$pc"};
const char* Register::DIGIT_OF_REGISTER[] = { "$0", "$1", "$2", "$3", "$4", "$5", "$6", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$16", "$17", "$18", "$19", "$20", "$21", "$22", "$23", "$24", "$25", "$26", "$27", "$28", "$29", "$30", "$31", "$32", "$33", "$34"};
const int Register::NAME_OF_REGISTER_SIZE = 35;
int Register::memoryOfRegister[Register::NAME_OF_REGISTER_SIZE];


int Register::toInt(const char* token) {
	int length = strlen(token);
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
Register::Register() {
	this->valuePtr = nullptr;
	this->haveToDeleteMemory = false;
}

//PART OF THIS CODE IS COMPILED
int* Register::getAddress(const char* token) { // This token have been eliminated space
	//TODO:
	int* ptr = nullptr;
	bool isOffset = true;
	int offSet;
	int valueRegister;
	int result;
	int beginToken = 0;
	for (int i = 0; i < strlen(token); ++i) {
		if (token[i] == '(' || token[i] == ')') {
			char* arg = new char[i - beginToken + 1];
			for (int k = 0; k < i - beginToken; ++k) {
				arg[k] = token[beginToken + k];
			}
			arg[i - beginToken] = 0;
			//do some thing
			if (isOffset) {
				offSet = toInt(arg);
				isOffset = false;
			}
			else
				for (int k = 0; k < NAME_OF_REGISTER_SIZE; ++k) {
					if (strcmp(NAME_OF_REGISTER[k], arg) == 0 || strcmp(DIGIT_OF_REGISTER[k], arg) == 0) {
						valueRegister = memoryOfRegister[k];
						break;
					}
				}
			delete[]arg;
			arg = nullptr;
			beginToken = i + 1;
		}
	}
	result = valueRegister + offSet;
	ptr = &result;
	return ptr;
}

// constructor for storing data not in memoryOfRegister
Register::Register(int _value) {
	this->valuePtr = new int;
	*(this->valuePtr) = _value;
	this->haveToDeleteMemory = true;
}

// For storing label adress.
Register::Register(void* source) {
	this->valuePtr = (int*)source;
	this->haveToDeleteMemory = false;
}

// Classify token as register, variable, label, constant.
Register::Register(const char* token) {
	// TODO: give compile error when source code try to access $hi, $lo, $pc.
	// TODO: give compile error when try to access undeclared label or unknow register.

	// Check if token is a register.
	for (int i = 0; i < NAME_OF_REGISTER_SIZE; ++i) {
		if (strcmp(NAME_OF_REGISTER[i], token) == 0 || strcmp(DIGIT_OF_REGISTER[i], token) == 0) {
			this->valuePtr = memoryOfRegister + i;
			this->haveToDeleteMemory = false;
			return;
		}	
	}
	//check if token is a Address e.g List+4($s1)
	for (int i = 0; i < strlen(token); ++i) {
		if (token[i] == '(') {
			this->valuePtr = (int*)getAddress(token);
			this->haveToDeleteMemory = true;
			return;
		}
	}


	// Check if token is a label.
	this->valuePtr = (int*) LabelManager::getLabel(token);
	if (this->valuePtr) {
		this->haveToDeleteMemory = false;
		return;
	}

	// token is constant.
	// TODO: if token is not a number, give compile error.
	// TODO: implement case that token is a real number.
	int value = toInt(token);
	this->valuePtr = new int;
	*valuePtr = value;
	this->haveToDeleteMemory = true;
}

// NEVER pass a (Register contain real memory) by value.
Register::Register(const Register& source) {
	this->valuePtr = new int(*source.valuePtr);
	this->haveToDeleteMemory = true;
}

Register::~Register() {
	if (this->haveToDeleteMemory)
		delete this->valuePtr;
}

Register& Register::operator=(const Register& operand) & {
	*(this->valuePtr) = *operand.valuePtr;
	return *this;
}

Register Register::operator+(const Register& operand) const & {
	return Register(*(this->valuePtr) + *operand.valuePtr);
}

Register Register::operator-(const Register& operand) const & {
	return Register(*(this->valuePtr) - *operand.valuePtr);
}

Register Register::operator&(const Register& operand) const & {
	return Register(*(this->valuePtr) & *operand.valuePtr);
}

Register Register::operator|(const Register& operand) const & {
	return Register(*(this->valuePtr) | *operand.valuePtr);
}

Register Register::operator<<(const Register& operand) const & {
	return Register(*(this->valuePtr) << *operand.valuePtr);
}

Register Register::operator>>(const Register& operand) const & {
	return Register(*(this->valuePtr) >> *operand.valuePtr);
}

Register Register::addUnsigned(const Register& operand) const & {
	return Register((unsigned int)*(this->valuePtr) + (unsigned int)*operand.valuePtr);
}

Register Register::subtractUnsigned(const Register& operand) const & {
	return Register((unsigned int) * (this->valuePtr) - (unsigned int)*operand.valuePtr);
}

Register Register::operator*(const Register& operand) const & {
	return Register(*(this->valuePtr) * *(operand.valuePtr));
}

int Register::getValue() {
	return *valuePtr;
}

int Register::advance(int amount) {
	*valuePtr += amount;
	return *valuePtr;
}

bool Register::operator==(const Register& operand) const & {
	return *(this->valuePtr) == *(operand.valuePtr);
}

bool Register::operator!=(const Register& operand) const & {
	return *(this->valuePtr) != *(operand.valuePtr);
}

bool Register::operator>(const Register& operand) const & {
	return *(this->valuePtr) > *(operand.valuePtr);
}

bool Register::operator>=(const Register& operand) const & {
	return *(this->valuePtr) >= *(operand.valuePtr);
}

bool Register::operator<(const Register& operand) const & {
	return *(this->valuePtr) < *(operand.valuePtr);
}

bool Register::operator<=(const Register& operand) const & {
	return *(this->valuePtr)  <= *(operand.valuePtr);
}

void Register::mult(const Register& operand) const & {
	Register hi("$hi");
	Register lo("$lo");
	long long result = (long long)*(this->valuePtr) * (long long)*(operand.valuePtr);
	long long* ptr = &result;
	*(hi.valuePtr) = ((int*)ptr)[1];
	*(lo.valuePtr) = ((int*)ptr)[0];
}

void Register::div(const Register& operand) const& {
	Register hi("$hi");
	Register lo("$lo");
	*(hi.valuePtr) = *(this->valuePtr) % *(operand.valuePtr);
	*(lo.valuePtr) = *(this->valuePtr) / *(operand.valuePtr);
}

Register Register::lui(const int digit) const& {
	return Register(*(this->valuePtr) << 16);
}