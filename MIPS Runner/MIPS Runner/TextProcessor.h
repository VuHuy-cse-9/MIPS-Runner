#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "Instruction.h"
#include "ThreeArgInstruction.h"

class TextProcessor
{
private:
	const int MAX_LINE_LENGTH = 255;
	// For storing source code data.
	char* sourceCode;
	int numberOfCharacter;

	Instruction** instructionList;
	int numberOfInstruction;

public:
	~TextProcessor();

	void readSourceFile();
	bool isIgnoreCharacter(char);
	void extractToken(char*, std::vector<char*>&);
	Instruction* parseTextToInstruction(char*);
	void parseSourceToInstruction();
	
};
