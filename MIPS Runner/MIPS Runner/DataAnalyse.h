#pragma once

#include <cstring>

#include "LabelManager.h"
#include "MemoryManager.h"
#include "TokenList.h"
#include "InstructionOperand.h"

class DataAnalyse
{
private:
	void* variable;
	int tokenListSize;
	static void* currentPtr;
	bool static isFirstMemory;
	void (*function) (TokenList&, int);

	static char parseBackslash(char);

	static void word(TokenList&,int);
	static void byte(TokenList&, int);
	static void half(TokenList&, int);
	static void Float(TokenList&, int);
	static void Double(TokenList&, int);
	static void space(TokenList&, int);
	static void ascii(TokenList&, int);
	static void asciiz(TokenList&, int);


public:
	DataAnalyse(const char*);
	void process(TokenList&);
//>>>>>>> b06f981eb9a89adaa73bc29ac0c461f61f33f001
};

