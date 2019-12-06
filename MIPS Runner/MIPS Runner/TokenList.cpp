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

int TokenList::getTokenListSize(const char* _line) {
	int i = 0;
	for (i = 0; _line[i] && _line[i] != ' '; ++i);
	if (!_line[i]) return 1;

	int size = 2;
	for (int i = 0; _line[i]; ++i)
		size += (_line[i] == ',');
	return size;
}

TokenList::TokenList(const char* _line) {
	tokenListSize = getTokenListSize(_line);
	tokenList = new char* [tokenListSize];

	int k = 0;
	int l = 0;
	for (int r = 0; true; ++r)
		if ((k == 0 && _line[r] == ' ') || _line[r] == ',' || _line[r] == '\0') {
			tokenList[k] = new char[r - l + 1];
			for (int i = l; i < r; ++i)
				tokenList[k][i - l] = _line[i];
			tokenList[k][r - l] = '\0';
			++k;
			l = r + 1;
			if (_line[r] == '\0') break;
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

char* TokenList::operator[](int i) {
	return tokenList[i];
}