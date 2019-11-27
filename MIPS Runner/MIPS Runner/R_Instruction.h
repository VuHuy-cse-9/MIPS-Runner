#pragma once

#include "Instruction.h"

class R_Instruction : public Instruction {
protected:
	int rd, rs, rt;

public:
	static const char instructionList[2][5];
};

const char R_Instruction::instructionList[2][5] = { "add\0", "addi" };
