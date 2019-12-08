#pragma once

#include "Instruction.h"
#include "InstructionOperand.h"
#include "SmartPointer.h"

class Processor
{
private:
	InstructionOperand pc;

	Processor();
	Processor(const Processor&) = delete;

	static SmartPointer<Processor> instance;

public:
	int instructionListSize;
	Instruction** instructionList;

	static Processor* getInstance();
	int run(); 
	int runNextInstruction();
};

