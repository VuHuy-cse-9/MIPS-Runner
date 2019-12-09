#include "DataAnalyse.h"

void* DataAnalyse::currentPtr = nullptr;
bool  DataAnalyse::isFirstMemory = false;

void DataAnalyse::process(TokenList& _tokenList) {
	function = nullptr;
	if (strcmp(_tokenList[0], ".word") == 0)	function = word;
	if (strcmp(_tokenList[0], ".byte") == 0)	function = byte;
	if (strcmp(_tokenList[0], ".half") == 0)	function = half;
	if (strcmp(_tokenList[0], ".ascii") == 0)	function = ascii;
	if (strcmp(_tokenList[0], ".asciiz") == 0)	function = asciiz;
	if (strcmp(_tokenList[0], ".space") == 0)	function = space;
	if (function)
		function(_tokenList, tokenListSize);
	else
		throw std::string("cannot evaluate \"") + std::string(_tokenList[0]) + std::string("\"");
}

DataAnalyse::DataAnalyse(const char* line) {
	TokenList tokenList(line);
	switch (tokenList.size())
	{
	case 1:
		variable = LabelManager::getInstance()->addVariableLabel(tokenList[0]);
		if (!isFirstMemory) isFirstMemory = true;
		break;
	default:
		process(tokenList);
		if (isFirstMemory) {
			isFirstMemory = false;
		}
		break;
	}
}

void DataAnalyse::word(TokenList& tokenList,int tokenListSize) {
	for (int i = 1; i < tokenList.size(); ++i) {
		InstructionOperand operand(tokenList[i]);
		if (!operand.signatureIs("Ii"))
			throw std::string("\"") + std::string(tokenList[i]) + std::string("\" have to be an integer");
		currentPtr = MemoryManager::getInstance()->allocateVariableMemory<int>(4, *(operand.memoryPtr));
	}
}		

void DataAnalyse::byte(TokenList& tokenList, int tokenListSize) {
	for (int i = 1; i < tokenList.size(); ++i) {
		InstructionOperand operand(tokenList[i]);
		if (*operand.memoryPtr < -128 || *operand.memoryPtr > 127)
			throw std::string("the initial value of byte have to be in between -128 and 127");
		if (!operand.signatureIs("Ii"))
			throw std::string(tokenList[i]) + std::string(" have to be a byte size integer");
		currentPtr = MemoryManager::getInstance()->allocateVariableMemory<int>(1, *(operand.memoryPtr));
	}
}

void DataAnalyse::half(TokenList& tokenList, int tokenListSize) {
	for (int i = 1; i < tokenList.size(); ++i) {
		InstructionOperand operand(tokenList[i]);
		if (*operand.memoryPtr < -32768 || *operand.memoryPtr > 32767)
			throw std::string("the initial value of half have to be in between -32768 and 32767");
		if (!operand.signatureIs("Ii"))
			throw std::string(tokenList[i]) + std::string(" have to be a half size integer");
		currentPtr = MemoryManager::getInstance()->allocateVariableMemory<int>(4, *(operand.memoryPtr));
	}
}


void DataAnalyse::space(TokenList& tokenList, int tokenListSize) {
	for (int i = 1; i < tokenList.size(); ++i) {
		InstructionOperand operand(tokenList[i]);
		currentPtr = MemoryManager::getInstance()->allocateVariableMemory<int>(*(operand.memoryPtr), 0);
	}
}

void DataAnalyse::ascii(TokenList& tokenList, int tokenListSize) {
	for (int i = 0; i < strlen(tokenList[1]); ++i) {
		if (tokenList[1][i] != '\"') {
			currentPtr = MemoryManager::getInstance()->allocateVariableMemory <char>(1, tokenList[1][i]);
		}
	}
}


void DataAnalyse::asciiz(TokenList& tokenList, int tokenListSize) {
	for (int i = 0; i < strlen(tokenList[1]); ++i) {
		if (tokenList[1][i] != '\"') {
			currentPtr = MemoryManager::getInstance()->allocateVariableMemory <char>(1, tokenList[1][i]);
		}
	}
	currentPtr = MemoryManager::getInstance()->allocateVariableMemory <char>(1, '\0');
}

