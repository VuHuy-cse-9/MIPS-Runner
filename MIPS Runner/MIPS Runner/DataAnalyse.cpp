#include "DataAnalyse.h"

float DataAnalyse::toFloat(const char* _token) {
	int length = strlen(_token);
	float result = 0;
	int begin = 0;
	float sign = 1.0;
	bool isUnit = true;
	int dec = 10;
	if (_token[0] == '-') {
		begin = 1;
		sign = -1.0;
	}
	for (int i = begin; i < length; ++i) {
		if (_token[i] == '.') {
			isUnit = false;
			++i;
		}
		if (isUnit) {
			result += (_token[i] - '0');
		}
		else {
			result += (_token[i] - '0') % dec;
			dec *= 10;
		}	
	}
	return result*sign;

}

int DataAnalyse::toInt(const char* _token) {
	//TODO:
	int length = strlen(_token);
	int result = 0;
	int begin = 0;
	int sign = 1;
	if (_token[0] == '-') {
		begin = 1;
		sign = -1;
	}
	for (int i = begin; i < length; ++i) {
		result = result * 10 + (_token[i] - '0');
	}
	return result * sign;
}

short DataAnalyse::toShort(const char* _token) {
	//TODO:
	int length = strlen(_token);
	short result = 0;
	int begin = 0;
	short sign = 1;
	if (_token[0] == '-') {
		begin = 1;
		sign = -1;
	}
	for (int i = begin; i < length; ++i) {
		result = result * 10 + (_token[i] - '0');
	}
	return result * sign;
}



void DataAnalyse::processor(TokenList& tokenList) {
	//TODO:
	if (tokenList[0] == ".word")	function = word;
	if (tokenList[0] == ".byte")	function = byte;
	if (tokenList[0] == ".half")	function = half;
	if (tokenList[0] == ".ascii")	function = ascii;
	if (tokenList[0] == ".asciiz")	function = asciiz;
	if (tokenList[0] == ".space")	function = space;
	function(tokenList, tokenListSize);
}



char** DataAnalyse::parseDataToToken(const char* line) {
	// tokenListSize count token list
	for (int i = 0; i < strlen(line); ++i) {
		if (line[i] == 0 || line[i] == ' ' || line[i] == ',') {
			++tokenListSize;
		}
	}
	char** tokenList = new char*[tokenListSize]; // list of token
	//parse
	int begin = 0;
	int orderToken = 0;
	for (int i = 0; i < strlen(line); ++i) {
		if (line[i] == ' ' || line[i] == ':' || line[i] == ',') {
			tokenList[orderToken] = new char[i];
			tokenList[i - 1] = 0;
			for (int k = 0; k < i - begin - 1; ++i) {
				tokenList[orderToken][k] = line[begin + k];
			}
			begin = i + 1;
			++orderToken;
		}
	}
	return tokenList;


}

DataAnalyse::DataAnalyse(const char* line) {
	TokenList tokenList(line);
	// if it is label ? - > tokenData will have one token -> 
	switch (tokenList.size())
	{
	case 1:
		LabelManager::getInstance()->addVariableLabel(tokenList[0]);
		break;
	default:
		processor(tokenList);
		break;
	}
}

void DataAnalyse::word(TokenList& tokenList,int tokenListSize) {
	bool isInt = true;
	for (int i = 1; i < tokenListSize; ++i) {
		for (int k = 0; k < strlen(tokenList[i]); ++k) {
			if (tokenList[i][k] == '.') isInt = false;
		}	
		if (isInt) currentPtr = MemoryManager::getInstance()->allocateVariableMemory <int>(4, toInt(tokenList[i]));
		else currentPtr = MemoryManager::getInstance()->allocateVariableMemory<float>(4, toFloat(tokenList[i]));
	}
}		

void DataAnalyse::byte(TokenList& tokenList, int tokenListSize) {
	for (int i = 1; i < tokenListSize; ++i) {
		// tokenlist[j] == \0 => eliminate
		for (int j = 0; j < strlen(tokenList[i]) - 1; ++j) {
			currentPtr = MemoryManager::getInstance()->allocateVariableMemory<char>(1, tokenList[i][j]);
		}
	}
}

void DataAnalyse::half(TokenList& tokenList, int tokenListSize) {
	for (int i = 1; i < tokenListSize; ++i) {
		currentPtr = MemoryManager::getInstance()->allocateVariableMemory <short>(2, toShort(tokenList[i]));
	}
}

void DataAnalyse::space(TokenList& tokenList, int tokenListSize) {
	currentPtr = MemoryManager::getInstance()->allocateVariableMemory <char>(toInt(tokenList[1]),'x');
}

void DataAnalyse::ascii(TokenList& tokenList, int tokenListSize) {
	for (int i = 0; i < strlen(tokenList[1]); ++i) {
		if (tokenList[1][i] != '"') {
			currentPtr = MemoryManager::getInstance()->allocateVariableMemory <char>(1, tokenList[1][i]);
		}
	}
}

void DataAnalyse::ascii(TokenList& tokenList, int tokenListSize) {
	for (int i = 0; i < strlen(tokenList[1]); ++i) {
		if (tokenList[1][i] != '"') {
			currentPtr = MemoryManager::getInstance()->allocateVariableMemory <char>(1, tokenList[1][i]);
		}
	}
}

void DataAnalyse::asciiz(TokenList& tokenList, int tokenListSize) {
	for (int i = 0; i < strlen(tokenList[1]); ++i) {
		if (tokenList[1][i] != '"') {
			currentPtr = MemoryManager::getInstance()->allocateVariableMemory <char>(1, tokenList[1][i]);
		}
	}
	currentPtr = MemoryManager::getInstance()->allocateVariableMemory <char>(1, 0);
}

