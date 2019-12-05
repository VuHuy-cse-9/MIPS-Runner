#include "TextProcessor.h"

Instruction* TextProcessor::parseLineToInstruction(char* line) {
	Instruction* instruction = nullptr;	
	
	TokenList tokenList(line); // Receive Data  -> other line we go to Datanalyse
	//->analyse : if it was a label? 

	int numberOfArgument = tokenList.size() - 1;
	switch (numberOfArgument) {
	case -1:
		// a empty line.
		instruction = nullptr;
		break;
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
		// TODO: give complie error.
		break;
	}

	return instruction;
}

char* TextProcessor::lineEnd(char* line) {
	while (*line != '\n' || *line != '\r') ++line;
	return line;
}

void TextProcessor::standarize(char*& line) {
	char* formatedLine = new char[MAX_LINE_LENGTH];
	// currentPosition is the current position of formatedLine.
	char* currentPosition = formatedLine;
	char* lineBegin = line;

	while (*line == ' ') ++line;
	while 

	delete[] lineBegin;
	line = formatedLine;
}

void TextProcessor::standarize() {
	char* line = new char[MAX_LINE_LENGTH];
	char* formatedSourceCode = new char[sourceCodeSize + 1];
	// currentPosition is the current position of formatedSourceCode.
	char* currentPosition = formatedSourceCode;
	char* sourceCodeBegin = sourceCode;

	while (*sourceCode) {
		char* sourceCodeEndLine = lineEnd(sourceCode);
		*sourceCodeEndLine = 0;
		strcpy(line, sourceCode);
		standarize(line);

		strcpy(currentPosition, line);
		currentPosition += strlen(line);
	}

	delete[] sourceCode;
	sourceCode = formatedSourceCode;
}

void TextProcessor::parseSourceToInstruction(Instruction**& _instructionList, int& _instructionListSize) {
	for (int i = 0; i < sourceCodeSize; ++i)
		if (sourceCode[i] == ':')
			sourceCode[i] = '\n';
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

			_instructionList[instructionCount] = parseTextToInstruction(line);
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