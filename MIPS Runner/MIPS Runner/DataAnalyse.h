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
	void (*function) (TokenList&,int);
	static void* currentPtr;
public:
	static float toFloat(const char*);
	static int toInt(const char*);
	static short toShort(const char*);
	DataAnalyse(const char*);
	void processor(TokenList&);
	static void word(TokenList&,int);
	static void byte(const char**, int);
	static void half(const char**, int);
	static void space(const char**, int);
	static void ascii(const char**, int);
	static void asciiz(const char**, int);
};

