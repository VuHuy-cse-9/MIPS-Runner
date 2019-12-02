#pragma once
#include"TextProcessor.h"
#include"Instruction.h"

class Processor
{
private:
	int numberOfInstruction;
	Instruction** instructionList;
	Register pc;

public:
	Processor(Instruction**&, const int&);
	int run(); // 0 => no bugs,1 bugs // run all code 
	int runNextInstruction(); // 0 => no bugs,1 bugs // step code
};

