#pragma once

#include"TextProcessor.h"
#include"Instruction.h"
#include "InstructionOperand.h"
#include "PrintDataRegister.h"

class Processor
{
private:
	int instructionListSize;
	Instruction** instructionList;
	InstructionOperand pc;

public:
	Processor(Instruction**&, const int&);
	int run(); // 0 => no bugs,1 bugs // run all code 
	int runNextInstruction(); // 0 => no bugs,1 bugs // step code
};

