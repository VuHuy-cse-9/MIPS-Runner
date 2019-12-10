#include "DataAnalyse.h"

void* DataAnalyse::currentPtr = nullptr;
bool  DataAnalyse::isFirstMemory = false;

void DataAnalyse::process(TokenList& _tokenList) {
	function = nullptr;
	if (strcmp(_tokenList[0], ".word") == 0)	function = word;
	if (strcmp(_tokenList[0], ".byte") == 0)	function = byte;
	if (strcmp(_tokenList[0], ".half") == 0)	function = half;
	if (strcmp(_tokenList[0], ".float") == 0)	function = Float;
	if (strcmp(_tokenList[0], ".double") == 0)	function = Double;
	if (strcmp(_tokenList[0], ".ascii") == 0)	function = ascii;
	if (strcmp(_tokenList[0], ".asciiz") == 0)	function = asciiz;
	if (strcmp(_tokenList[0], ".space") == 0)	function = space;
	if (function)
		function(_tokenList, tokenListSize);
	else
		throw std::string("cannot evaluate \"") + std::string(_tokenList[0]) + std::string("\"");
}

char DataAnalyse::parseBackslash(char c) {
	switch (c) {
	case '\'':
		return '\'';
	case '\"':
		return '\"';
	case '\?':
		return '\?';
	case '\\':
		return '\\';
	case 'a':
		return '\a';
	case 'b':
		return '\b';
	case 'f':
		return '\f';
	case 'n':
		return '\n';
	case 'r':
		return '\r';
	case 't':
		return '\t';
	case 'v':
		return '\v';
	case '0':
		return '\0';
	}
	return ' ';
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

void DataAnalyse::Float(TokenList& tokenList, int tokenListSize) {
	for (int i = 1; i < tokenList.size(); ++i) {
		InstructionOperand operand(tokenList[i]);
		if (operand.signatureIs("If"))
			currentPtr = MemoryManager::getInstance()->allocateVariableMemory<float>(4, *((double*)operand.memoryPtr));
		else if (operand.signatureIs("Ii"))
			currentPtr = MemoryManager::getInstance()->allocateVariableMemory<float>(4, *operand.memoryPtr);
		else 
			throw std::string(tokenList[i]) + std::string(" have to be a floating point number");
	}
}

void DataAnalyse::Double(TokenList& tokenList, int tokenListSize) {
	for (int i = 1; i < tokenList.size(); ++i) {
		InstructionOperand operand(tokenList[i]);
		if (operand.signatureIs("If"))
			currentPtr = MemoryManager::getInstance()->allocateVariableMemory<float>(4, *((double*)operand.memoryPtr));
		else if (operand.signatureIs("Ii"))
			currentPtr = MemoryManager::getInstance()->allocateVariableMemory<float>(4, *operand.memoryPtr);
		else
			throw std::string(tokenList[i]) + std::string(" have to be a floating point number");
	}
}

void DataAnalyse::space(TokenList& tokenList, int tokenListSize) {
	for (int i = 1; i < tokenList.size(); ++i) {
		InstructionOperand operand(tokenList[i]);
		if (!operand.signatureIs("Ii"))
			throw std::string("the space define value have to be an integer");
		currentPtr = MemoryManager::getInstance()->allocateVariableMemory<int>(*(operand.memoryPtr), 0);
	}
}

void DataAnalyse::ascii(TokenList& tokenList, int tokenListSize) {
	int i = 0;
	while (tokenList[1][i] != '\"' && tokenList[1][i]) ++i;
	++i;

	while (tokenList[1][i] && tokenList[1][i] != '\"') {
		char value = ' ';
		if (tokenList[1][i] == '\\') {
			value = parseBackslash(tokenList[1][i + 1]);
			++i;
		}
		else
			value = tokenList[1][i];
		MemoryManager::getInstance()->allocateVariableMemory<char>(1, value);
		++i;
	}
}


void DataAnalyse::asciiz(TokenList& tokenList, int tokenListSize) {
	ascii(tokenList, tokenListSize);
	currentPtr = MemoryManager::getInstance()->allocateVariableMemory <char>(1, '\0');
}

