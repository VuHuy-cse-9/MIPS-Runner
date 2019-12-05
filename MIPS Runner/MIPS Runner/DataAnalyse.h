#pragma once
#include  <iostream>
#include "LabelManager.h"
#include "MemoryManager.h"

class DataAnalyse
{
private:
	void* variablePtr;
	char** tokenData;
	int tokenListSize;
	char** parseDataToToken(const char* );
	void (*function) (const char**,int);
	static void* currentPtr;
public:
	static int toInt(const char*);
	DataAnalyse(const char*);
	void processor(const char**);
	static void word(const char**,int);
	static void byte(const char**, int);
};

