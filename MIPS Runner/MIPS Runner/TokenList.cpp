#include "TokenList.h"


const int TokenList::MAX_SIZE = 5;

bool TokenList::isDelimiter(char c) {
	switch (c) {
	case ' ':
	case ',':
	case '\t':
	case '\n':
	case '\0':
		return 1;
	default:
		return 0;
	}
}

TokenList::TokenList (char* line) {
	tokenListSize = 0;
	tokenList = new char* [MAX_SIZE];
	int i = 0;
	while (line[i] != 0) {
		if (!isDelimiter(line[i])) {
			int run = i;
			while (!isDelimiter(line[run])) {
				++run;
			}
			char* token = new char[run - i + 1];
			for (int j = 0; j < run - i; ++j) {
				token[j] = line[i + j];
			}
			token[run - i] = 0;
			pushBack(token);
			i = run;
			delete[] token;
		}
		else
			++i;
	}
}

TokenList::~TokenList() {
	for (int i = 0; i < tokenListSize; ++i) {
		delete[] tokenList[i];
	}
	delete[] tokenList;
}

int TokenList::size() {
	return tokenListSize;
}

void TokenList::pushBack(char* token) {
	int i = 0;
	while (token[i] != 0) {
		++i;
	}
	tokenList[tokenListSize] = new char[i + 1];
	strcpy(tokenList[tokenListSize], token);
	++tokenListSize;
}

char*& TokenList::operator[](int i) {
	return tokenList[i];
}