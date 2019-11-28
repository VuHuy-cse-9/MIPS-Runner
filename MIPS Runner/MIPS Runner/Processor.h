#pragma once

#include <iostream>
#include <fstream>

#include "Instruction.h"
#include "R_Instruction.h"

class Processor
{
private:
	const int MAX_LINE_LENGTH = 255;
	// For storing source code data.
	char* sourceCode;
	int numberOfCharacter;

	Instruction** instructionList;
	int numberOfInstruction;

public:
	~Processor();

	void readSourceFile();
	Instruction* parseTextToInstruction(char*);
	void parseSourceToInstruction();
};


