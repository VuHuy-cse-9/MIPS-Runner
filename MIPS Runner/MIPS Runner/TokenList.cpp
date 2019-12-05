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

TokenList::TokenList (const char* line) {
	tokenListSize = 0;
	tokenList = new char* [MAX_SIZE];

	int i = 0;
	int run = 0;
	while (line[i] != 0) {
		if (i == 0) {
			while (isDelimiter(line[i])) i++;
			run = i;
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
			while (isDelimiter(line[i])) i++;
			delete[] token;
		}
		else {
			run = i;
			int count = 0;
			while (line[run] != ',' && line[run] != 0) {
				if (line[run] != ' ') {
					++count;
				}
				++run;
			}
			char* token = new char[count + 1];
			token[count] = 0;
			int j = 0;
			for (int k = 0; k < run - i; ++k) {
				if (line[i + k] != ' ') {
					token[j] = line[i + k];
					++j;
				}
			}
			pushBack(token);
			if (line[run] != 0)
				i = run + 1;
			else i = run;
		}
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
	return this->tokenList[i];
}