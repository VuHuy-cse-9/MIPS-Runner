#include "TokenList.h"


const int TokenList::MAX_SIZE = 4;

TokenList::TokenList() {
	numberOfToken = 0;
	tokenList = new char*[MAX_SIZE];
}

TokenList::~TokenList() {
	for (int i = 0; i < numberOfToken; ++i) {
		delete[] tokenList[i];
	}
	delete[] tokenList;
}

int TokenList::size() {
	return numberOfToken;
}

void TokenList::pushBack(char* token) {
	int i = 0;
	while (token[i] != 0) {
		++i;
	}
	tokenList[numberOfToken] = new char[i + 1];
	strcpy(tokenList[numberOfToken], token);
	++numberOfToken;
}

char*& TokenList::operator[](int i) {
	return tokenList[i];
}