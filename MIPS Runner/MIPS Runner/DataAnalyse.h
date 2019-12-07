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
	char** parseDataToToken(const char* );
	static void* currentPtr;
	void* (*function) (TokenList&, int);
public:
	bool static isFirstMemory;
	DataAnalyse(const char*);
	static float toFloat(const char*);
	static int toInt(const char*);
	static short toShort(const char*);
	void* process(TokenList&);
	static void* word(TokenList&,int);
	static void* byte(TokenList&, int);
	static void* half(TokenList&, int);
	static void* space(TokenList&, int);
	static void* ascii(TokenList&, int);
	static void* asciiz(TokenList&, int);
};

