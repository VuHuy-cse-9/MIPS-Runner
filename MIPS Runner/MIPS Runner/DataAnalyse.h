#pragma once

#include <cstring>

#include "LabelManager.h"
#include "MemoryManager.h"
#include "TokenList.h"
#include "InstructionOperand.h"

class DataAnalyse
{
private:
	int tokenListSize;
	static void* currentPtr;
	void (*function) (TokenList&, int);

	static void word(TokenList&,int);
	static void byte(TokenList&, int);
	static void half(TokenList&, int);
	static void space(TokenList&, int);
	static void ascii(TokenList&, int);
	static void asciiz(TokenList&, int);


public:
	DataAnalyse(const char*);
	void process(TokenList&);
};

