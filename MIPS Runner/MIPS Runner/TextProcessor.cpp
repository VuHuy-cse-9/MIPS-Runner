#include "TextProcessor.h"

Instruction* TextProcessor::parseLineToInstruction(char* line) {
	Instruction* instruction = nullptr;	
	
	TokenList tokenList(line);

	int numberOfArgument = tokenList.size() - 1;
	switch (numberOfArgument) {
	case 0:
		instruction = new ZeroArgInstruction(tokenList);
		break;
	case 1:
		instruction = new OneArgInstruction(tokenList);
		break;
	case 2:
		instruction = new TwoArgInstruction(tokenList);
		break;
	case 3:
		instruction = new ThreeArgInstruction(tokenList);
		break;
	default:
		throw std::string("\"") + std::string(line) + std::string("\" have to many arguments");
		break;
	}

	return instruction;
}

bool TextProcessor::isSpacing(char c) {
	switch (c) {
	case ' ':
	case '\t':
		return true;
	default:
		return false;
	}
}

bool TextProcessor::isEmptyLine(const char* line) {
	for (int i = 0; line[i]; ++i)
		if (!isSpacing(line[i])) return false;
	return true;
}

char* TextProcessor::lineEnd(char* line) {
	while (*line != '\n' && *line != '\r') 
		++line;
	return line;
}

void TextProcessor::standarize(char*& line) {
	// the end of formatedSourceCode contain "\n\0".

	// check if line is an empty line.
	if (isEmptyLine(line)) {
		line[0] = 0;
		return;
	}
	
	char* formatedLine = new char[MAX_LINE_LENGTH];
	// currentPosition is the current position of formatedLine.
	char* currentPosition = formatedLine;
	char* lineBegin = line;

	// Extract label(s).
	bool newLine = false;
	do
	{
		bool isLabel = false;
		int i;
		for (i = 0; line[i]; ++i)
			if (line[i] == ':') {
				isLabel = true;
				break;
			}
		if (!isLabel) break;

		char* newLineBegin = line + i + 1;
		while (isSpacing(*line)) ++line, --i;
		while (isSpacing(line[i - 1])) --i;

		for (int j = 0; j < i; ++j) 
			*(currentPosition++) = line[j];
		*(currentPosition++) = ':';
		*(currentPosition++) = '\n';

		line = newLineBegin;
	} while (true);

	if (isEmptyLine(line)) {
		delete[] lineBegin;
		*(currentPosition++) = '\0';
		line = formatedLine;
		return;
	}

	// Extract opcode (add, addi, .word, .space, .data, .text, ...).
	while (isSpacing(*line)) ++line;
	if (!*line) {
		delete[] lineBegin;
		*(currentPosition++) = '\n';
		*(currentPosition++) = '\0';
		line = formatedLine;
		return;
	}
	while (!isSpacing(*line) && *line)
		*(currentPosition++) = *(line++);
	*(currentPosition++) = ' ';
	if (!*line) {
		delete[] lineBegin;
		*(currentPosition++) = '\n';
		*(currentPosition++) = '\0';
		line = formatedLine;
		return;
	}

	// Extract argument(s).
	do
	{
		while (isSpacing(*line)) ++line;

		while (*line != ',' && *line)
			*(currentPosition++) = *(line++);
		while (isSpacing(*(currentPosition - 1))) currentPosition--;

		if (!*line) break;
		*(currentPosition++) = *(line++);

	} while (true);

	delete[] lineBegin;
	*(currentPosition++) = '\n';
	*(currentPosition++) = '\0';
	line = formatedLine;
}

void TextProcessor::standarize() {
	char* formatedSourceCode = new char[sourceCodeSize + 1];
	// currentPosition is the current position of formatedSourceCode.
	char* currentPosition = formatedSourceCode;
	char* sourceCodeBegin = sourceCode;

	char* line = new char[MAX_LINE_LENGTH];
	while (*sourceCode) {
		char* sourceCodeEndLine = lineEnd(sourceCode);
		*sourceCodeEndLine = 0;
		strcpy(line, sourceCode);
		standarize(line);

		strcpy(currentPosition, line);
		currentPosition += strlen(line);
		sourceCode = sourceCodeEndLine + 1;
	}
	
	delete[] sourceCodeBegin;
	sourceCode = formatedSourceCode;
}

void TextProcessor::parseSourceToInstruction(Instruction**& _instructionList, int& _instructionListSize) {
	standarize();
	std::cout << sourceCode;
	// Count the number of instructions and allocate memory for them.
	_instructionListSize = 0;
	for (int i = 0; i < sourceCodeSize; ++i) 
		if (sourceCode[i] == '\n')
			++_instructionListSize;
	_instructionList = new Instruction*[_instructionListSize];

	//  Extract line from source code to parse it.
	char* line = new char[MAX_LINE_LENGTH];
	int begin = 0;
	int instructionCount = 0;
	for (int i = 0; i < sourceCodeSize; ++i) 
		if (sourceCode[i] == '\n') {
			for (int j = 0; j < i - begin; ++j) 
				line[j] = sourceCode[begin + j];
			line[i - begin] = 0;

			_instructionList[instructionCount] = parseLineToInstruction(line);
			if (_instructionList[instructionCount])
				++instructionCount;

			begin = i + 1;
		}
	_instructionListSize = instructionCount;
	delete[] line;
}

// TODO: replace constant "source.mips" with dynamic file name.
void TextProcessor::readSourceFile() {
	std::ifstream inputFile("source.mips");
	
	inputFile.seekg(0, inputFile.end);
	sourceCodeSize = inputFile.tellg();
	inputFile.seekg(0, inputFile.beg);

	sourceCode = new char[sourceCodeSize + 2];

	int i = 0;
	while (!inputFile.eof()) {
		inputFile.getline(sourceCode + i, sourceCodeSize + 2);
		i += inputFile.gcount();
		if (sourceCode[i - 1] == 0) sourceCode[i - 1] = '\n';
	}

	sourceCodeSize = i + 1;
	sourceCode[sourceCodeSize - 1] = '\n';
	sourceCode[sourceCodeSize] = 0;
}

TextProcessor::~TextProcessor() {
	delete[] sourceCode;
}