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
	char* signature;

	bool isDelimiter(char);
	int getTokenListSize(const char*);

public:
	TokenList(const char* line);
	~TokenList();

	int size();
	char* operator[](int);
};

