#pragma once

#include <cstring>

#include "Instruction.h"

class R_Instruction : public Instruction {
protected:
	int rd, rs, rt;
	void (*function)(int&, int, int);
public:
	static const char* R_INSTRUCTION_LIST[];
	static const int R_INSTRUCTION_LIST_SIZE;

	R_Instruction(const char*);

	void execute() override;
};

const char* R_Instruction::R_INSTRUCTION_LIST[] = {"add", "sub", "and", "or"};
const int R_Instruction::R_INSTRUCTION_LIST_SIZE = 4;