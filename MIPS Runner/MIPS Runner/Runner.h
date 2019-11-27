#pragma once

#include <iostream>
#include <fstream>

#include "Instruction.h"

class Runner
{
private:
	// For storing source code data.
	char** file;
	int numberOfLine;

	Instruction* instructionList[50];

public:
	~Runner();

	void readSourceFile();
	Instruction* parseTextToInstruction(char*);
	void parseSourceToInstruction();
};


