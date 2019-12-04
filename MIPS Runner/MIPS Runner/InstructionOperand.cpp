#include "InstructionOperand.h"

int InstructionOperand::toInt(const char* _token) {
	int length = strlen(_token);
	int result = 0;
	int begin = 0;
	int sign = 1;
	if (_token[0] == '-') {
		begin = 1;
		sign = -1;
	}
	for (int i = begin; i < length; ++i) {
		result = result * 10 + (_token[i] - '0');
	}
	return result * sign;
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

InstructionOperand::InstructionOperand(const char* _token) {
	this->memoryPtr = nullptr;
	this->offset = 0;
	this->haveToDeleteMemory = false;

	this->memoryPtr = MemoryManager::getInstance()->getRegister(_token);
	if (this->memoryPtr) return;

	this->memoryPtr = (int*) LabelManager::getInstance()->getMemory(_token);
	if (this->memoryPtr) return;

	parseRegisterWithOffSet(_token);
	if (this->memoryPtr) return;

	this->memoryPtr = new int;
	*(this->memoryPtr) = toInt(_token);
	this->haveToDeleteMemory = true;
}

InstructionOperand::~InstructionOperand() {
	if (haveToDeleteMemory)
		delete this->memoryPtr;
}