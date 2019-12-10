#include "InstructionOperand.h"

int InstructionOperand::toInt(const char* _token, bool& success) {
	int begin = 0;
	int sign = 1;
	if (_token[0] == '-') {
		begin = 1;
		sign = -1;
	}

	success = false;
	for (int i = begin; _token[i]; ++i)
		if (_token[i] < '0' || _token[i] > '9') return 0;
	success = true;

	int result = 0;
	for (int i = begin; _token[i]; ++i) {
		result = result * 10 + (_token[i] - '0');
	}
	return result * sign;
}

double InstructionOperand::toDouble(const char* _token, bool& success) {
	int begin = 0;
	int sign = 1;
	if (_token[0] == '-') {
		begin = 1;
		sign = -1;
	}

	success = false;
	int countDot = 0;
	int base = 1;
	for (int i = begin; _token[i]; ++i) {
		if ((_token[i] < '0' || _token[i] > '9') && _token[i] != '.') return 0;
		if (countDot > 0) base *= 10;
		countDot += (_token[i] == '.');
	}
	if (countDot > 1) return 0;
	if (_token[begin] == '.') return 0;
	success = true;

	double result = 0;
	for (int i = begin; _token[i]; ++i)
		if (_token[i] != '.')
			result = result * 10 + _token[i] - '0';
	return sign * result / base;
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

	this->memoryPtr = (int*)MemoryManager::getInstance()->getFloatingPointRegister(_token);
	if (this->memoryPtr) {
		//TODO:Toan do something to compile
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

	throw std::string("cannot evaluate \"") + std::string(_token) + std::string("\"");
}

InstructionOperand::~InstructionOperand() {
	if (haveToDeleteMemory)
		delete this->memoryPtr;
}

bool InstructionOperand::signatureIs(const char* _signature) {
	return (this->signature[0] == _signature[0] && this->signature[1] == _signature[1]);
}