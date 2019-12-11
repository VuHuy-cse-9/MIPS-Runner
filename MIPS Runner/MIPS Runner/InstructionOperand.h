#pragma once

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include <string>

#include "MemoryManager.h"
#include "LabelManager.h"

class InstructionOperand
{
private:
	bool haveToDeleteMemory;
	int HexToDec(const char*, bool&);
	int toInt(const char*, bool&);
	double toDouble(const char*, bool&);
	void parseRegisterWithOffSet(const char*);
public:
	int* memoryPtr;
	int offset;
	char signature[2];

	InstructionOperand(int*, int);
	InstructionOperand(const char*);
	~InstructionOperand();

	bool signatureIs(const char*);
};