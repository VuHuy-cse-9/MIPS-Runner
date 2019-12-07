#include "DataAnalyse.h"

void* DataAnalyse::currentPtr = nullptr;
bool  DataAnalyse::isFirstMemory = false;

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



void* DataAnalyse::process(TokenList& _tokenList) {
	//TODO:
	function = nullptr;
	if (strcmp(_tokenList[0],".word") == 0)	function = word;
	if (strcmp(_tokenList[0], ".byte") == 0)	function = byte;
	if (strcmp(_tokenList[0], ".half") == 0)	function = half;
	if (strcmp(_tokenList[0], ".ascii") == 0)	function = ascii;
	if (strcmp(_tokenList[0], ".asciiz") == 0)	function = asciiz;
	if (strcmp(_tokenList[0], ".space") == 0)	function = space;
	if (function)
		return function(_tokenList, tokenListSize);
	else return NULL;
}

DataAnalyse::DataAnalyse(const char* line) {
	TokenList tokenList(line);
	for (int i = 0; i < tokenList.size(); ++i) {
		std::cout << tokenList[i] << '\n';
	}
	int x = tokenList.size();
	std::cout << x;
	switch (tokenList.size())
	{
	case 2:
		variable = LabelManager::getInstance()->addVariableLabel(tokenList[0]); // give pointer here
		if (!isFirstMemory) isFirstMemory = true;
		std::cout << "access";
		break;
	default:
		void* ptr = process(tokenList);
		if (isFirstMemory) {
			variable = ptr;
			//std::cout << *((int*)variable) << "access";
			isFirstMemory = false;
		}
		break;
	}
}

void* DataAnalyse::word(TokenList& tokenList,int tokenListSize) {
	void* head = nullptr;
	for (int i = 1; i < tokenList.size(); ++i) {
		InstructionOperand token(tokenList[i]);
		currentPtr = MemoryManager::getInstance()->allocateVariableMemory<int>(4, *(token.memoryPtr));
		if (i == 1) head = currentPtr;
	}
	return head;
}		

void* DataAnalyse::byte(TokenList& tokenList, int tokenListSize) {
	void* head = nullptr;
	for (int i = 1; i < tokenList.size(); ++i) {
		// tokenlist[j] == \0 => eliminate
		for (int j = 0; j < strlen(tokenList[i]); ++j) {
			currentPtr = MemoryManager::getInstance()->allocateVariableMemory<char>(1, tokenList[i][j]);
		}
		if (i == 1) head = currentPtr;
	}
	return head;
}

void* DataAnalyse::half(TokenList& tokenList, int tokenListSize) {
	void* head = nullptr;
	for (int i = 1; i < tokenList.size(); ++i) {
		currentPtr = MemoryManager::getInstance()->allocateVariableMemory <short>(2, toShort(tokenList[i]));
		if (i == 1) head = currentPtr;
	}
	return head;
}

void* DataAnalyse::space(TokenList& tokenList, int tokenListSize) {
	currentPtr = MemoryManager::getInstance()->allocateVariableMemory <char>(toInt(tokenList[1]),'0');
	return currentPtr;
}

void* DataAnalyse::ascii(TokenList& tokenList, int tokenListSize) {
	void* head = nullptr;
	for (int i = 0; i < strlen(tokenList[1]); ++i) {
		if (tokenList[1][i] != '"') {
			currentPtr = MemoryManager::getInstance()->allocateVariableMemory <char>(1, tokenList[1][i]);
		}
		if (i == 0) head = currentPtr;
	}
	return head;
}


void* DataAnalyse::asciiz(TokenList& tokenList, int tokenListSize) {
	void* head = nullptr;
	for (int i = 0; i < strlen(tokenList[1]); ++i) {
		if (tokenList[1][i] != '"') {
			currentPtr = MemoryManager::getInstance()->allocateVariableMemory <char>(1, tokenList[1][i]);
			if (i == 1) head = currentPtr;
		}
	}
	currentPtr = MemoryManager::getInstance()->allocateVariableMemory <char>(1, 0);
	return head;
}

