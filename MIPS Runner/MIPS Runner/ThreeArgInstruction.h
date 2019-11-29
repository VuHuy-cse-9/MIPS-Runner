#pragma once

#include <cstring>
#include <iostream>

#include "Instruction.h"

class ThreeArgInstruction : public Instruction {
protected:
	int rd, rs, rt;
	void (*function)(int&, int, int);
public:
	static const char* THREE_ARG_INSTRUCTION_LIST[];
	static const int THREE_ARG_INSTRUCTION_LIST_SIZE;

	ThreeArgInstruction(const char*);

	void execute() override;
};