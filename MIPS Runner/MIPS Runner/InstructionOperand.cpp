#include "InstructionOperand.h"

int InstructionOperand::toInt(const char* _token, bool& success) {
	int value;
	success = (sscanf(_token, "%d", &value) == 1);
	return value;
}

double InstructionOperand::toDouble(const char* _token, bool& success) {
	double value;
	success = (sscanf(_token, "%lf", &value) == 1);
	return value;
}

//TODO:need to update ($s3)
void InstructionOperand::parseRegisterWithOffSet(const char* _token) {
	bool isOffset = true;
	int beginToken = 0;
	for (int i = 0; i < strlen(_token); ++i) {
		if (_token[i] == '(' || _token[i] == ')') {
			bool convertSuccess;
			if (i == 0) {
				isOffset = false;
				beginToken = i + 1;
				convertSuccess = true;
				offset = 0;
			}
			else {
				char* arg = new char[i - beginToken + 1];
				for (int k = 0; k < i - beginToken; ++k) {
					arg[k] = _token[beginToken + k];
				}
				arg[i - beginToken] = 0;
				//do some thing
				if (isOffset) {
					offset = toInt(arg, convertSuccess);
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
		this->signature[1] = 'v';
		if (LabelManager::getInstance()->lastestLabelIsInstruction())
			this->signature[1] = 'i';
		return;
	}

	parseRegisterWithOffSet(_token);
	if (this->memoryPtr) {
		this->signature[0] = 'R';
		this->signature[1] = 'w';
		return;
	}

	this->signature[0] = 'I';
	bool convertSuccess = false;

	this->memoryPtr = new int;
	*(this->memoryPtr) = toInt(_token, convertSuccess);
	if (convertSuccess) {
		this->signature[1] = 'i';
		return;
	}
	delete this->memoryPtr;

	this->memoryPtr = (int*) new double;
	*(double*)(this->memoryPtr) = toDouble(_token, convertSuccess);
	if (convertSuccess) {
		this->signature[1] = 'f';
		return;
	}
	delete this->memoryPtr;

	throw std::string("cannot evaluate ") + std::string(_token);
}

InstructionOperand::~InstructionOperand() {
	if (haveToDeleteMemory)
		delete this->memoryPtr;
}