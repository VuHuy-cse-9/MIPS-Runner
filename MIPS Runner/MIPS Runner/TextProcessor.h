#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "Instruction.h"
#include "ZeroArgInstruction.h"
#include "OneArgInstruction.h"
#include "TwoArgInstruction.h"
#include "ThreeArgInstruction.h"
#include "TokenList.h"

class TextProcessor
{
private:
	const int MAX_LINE_LENGTH = 255;
	// For storing source code data.
	char* sourceCode;
	int numberOfCharacter;

	bool isIgnoreCharacter(char);
	void extractToken(char*, TokenList&);
	Instruction* parseTextToInstruction(char*);

public:
	~TextProcessor();

	void readSourceFile();
	void parseSourceToInstruction(Instruction**&, int&);
	
};
