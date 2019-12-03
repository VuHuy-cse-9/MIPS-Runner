#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <cstring>

class TokenList
{
private:
	static const int MAX_SIZE;
	int tokenListSize;
	char** tokenList;
	bool isDelimiter(char);
public:
	TokenList(char* line);
	~TokenList();
	int size();
	void pushBack(char*);
	char*& operator[](int);
};

