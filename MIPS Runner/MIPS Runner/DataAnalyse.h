#pragma once
#include  <iostream>
#include "LabelManager.h"
#include "MemoryManager.h"
#include "TokenList.h"

class DataAnalyse
{
private:
	int tokenListSize;
	char** parseDataToToken(const char* );
	static void* currentPtr;
public:
	static float toFloat(const char*);
	static int toInt(const char*);
	static short toShort(const char*);
	DataAnalyse(const char*);
	void processor(TokenList&);
	static void word(TokenList&,int);
	static void byte(TokenList&, int);
	static void half(TokenList&, int);
	static void space(TokenList&, int);
	static void ascii(TokenList&, int);
	static void asciiz(TokenList&, int);
};

