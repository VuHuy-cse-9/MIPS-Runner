#pragma once

#include "MemoryManager.h"
#include "LabelManager.h"

class InstructionOperand
{
private:
	bool haveToDeleteMemory;

	int toInt(const char*);
	void parseRegisterWithOffSet(const char*);
public:
	int* memoryPtr;
	int offset;

	InstructionOperand(int*, int);
	InstructionOperand(const char*);
	~InstructionOperand();
};

