#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include <iostream>
#include <fstream>
#include <vector>

#include "Instruction.h"
#include "ZeroArgInstruction.h"
#include "OneArgInstruction.h"
#include "TwoArgInstruction.h"
#include "ThreeArgInstruction.h"
#include "TokenList.h"
#include "DataAnalyse.h"

class TextProcessor
{
private:
	const int MAX_LINE_LENGTH = 255;
	// For storing source code data.
	char* sourceCode;
	int sourceCodeSize;

	bool isSpacing(char);
	char* lineEnd(char*);
	void standarize(char*&);
	void standarize();
	Instruction* parseLineToInstruction(char*);

public:
	~TextProcessor();

	void readSourceFile();
	void parseSourceToInstruction(Instruction**&, int&);
	
};
