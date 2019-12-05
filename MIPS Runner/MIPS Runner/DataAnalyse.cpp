#include "DataAnalyse.h"

int DataAnalyse::toInt(const char* token) {
	//TODO:
}



void DataAnalyse::processor(const char** tokenList) {
	//TODO:
	//recognize if it was e.g .word ? 
	if (tokenList[0] == ".word")	function = word;
	if (tokenList[0] == ".byte")	function = word;
	//if (tokenList[0] == ".half")	function = word;
	//if (tokenList[0] == ".ascii")	function = word;
	//if (tokenList[0] == ".asciiz")	function = word;
	//if (tokenList[0] == ".space")	function = word;
	//if (tokenList[0] == ".align")	function = word;
}

char** DataAnalyse::parseDataToToken(const char* line) {
	// tokenListSize count token list
	for (int i = 0; i < strlen(line); ++i) {
		if (line[i] == 0 || line[i] == ' ') {
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
	tokenData = parseDataToToken(line);
	// if it is label ? - > tokenData will have one token -> 
	switch (tokenListSize)
	{
	case 1:
		variablePtr = LabelManager::getInstance()->addVariableLabel(tokenData[0]); //label is saved in labelmanager
		break;
	default:
		//analyse data here
		processor(tokenData); // We have a list of token here
		break;
	}
}

void DataAnalyse::word(const char** tokenList,int tokenListSize) {
	for (int i = 1; i < tokenListSize; ++i) {
		currentPtr = MemoryManager::getInstance()->allocateVariableMemory <int>(4, toInt(tokenList[i]));
	}
}		

void DataAnalyse::byte(const char** tokenList, int tokenListSize) {
	for (int i = 1; i < tokenListSize; ++i) {
		for (int j = 0; j < tokenListSize; ++j) {
			currentPtr = MemoryManager::getInstance()->allocateVariableMemory<char>(1, tokenList[i][j]);
		}
	}
}