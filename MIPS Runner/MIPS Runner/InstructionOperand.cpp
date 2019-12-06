#include "InstructionOperand.h"

int InstructionOperand::toInt(const char* _token) {
	int value;
	if (sscanf(_token, "%d", &value) == EOF)
		throw "Not an Integer";
	return value;
}

float InstructionOperand::toFloat(const char* _token) {
	float value;
	if (sscanf(_token, "%f", &value) == EOF)
		throw "Not a Float";
	return value;
}

//TODO:need to update ($s3)
void InstructionOperand::parseRegisterWithOffSet(const char* _token) {
	bool isOffset = true;
	int beginToken = 0;
	for (int i = 0; i < strlen(_token); ++i) {
		if (_token[i] == '(' || _token[i] == ')') {
			char* arg = new char[i - beginToken + 1];
			for (int k = 0; k < i - beginToken; ++k) {
				arg[k] = _token[beginToken + k];
			}
			arg[i - beginToken] = 0;
			//do some thing
			if (isOffset) {
				offset = toInt(arg);
				isOffset = false;
			}
			else
				this->memoryPtr = MemoryManager::getInstance()->getRegister(arg);
			delete[]arg;
			arg = nullptr;
			beginToken = i + 1;
		}
	}
}

InstructionOperand::InstructionOperand(int* _memory, int _offset) 
	: memoryPtr(_memory), offset(_offset), haveToDeleteMemory(false) {
}

InstructionOperand::InstructionOperand(const char* _token) {
	this->memoryPtr = nullptr;
	this->offset = 0;
	this->haveToDeleteMemory = false;

	this->memoryPtr = MemoryManager::getInstance()->getRegister(_token);
	if (this->memoryPtr) {
		this->signature[0] = 'R';
		this->signature[1] = 'b';
		return;
	}

	this->memoryPtr = (int*) LabelManager::getInstance()->getMemory(_token);
	if (this->memoryPtr) {
		this->signature[0] = 'L';
		return;
	}

	parseRegisterWithOffSet(_token);
	if (this->memoryPtr) {
		signature[0] = 'R';
		signature[1] = 'w';
		return;
	}
	
	try {
		this->memoryPtr = new int;
		*(this->memoryPtr) = toInt(_token);
		this->haveToDeleteMemory = true;
	}
	catch (...) {
		try {
			this->memoryPtr = (int*)new float;
				*(float*)(this->memoryPtr) = toFloat(_token);
		}
		catch (...) {
			throw std::string("cannot evaluate \"") + std::string(_token) + std::string("\"");
		}
	}
}

InstructionOperand::~InstructionOperand() {
	if (haveToDeleteMemory)
		delete this->memoryPtr;
}