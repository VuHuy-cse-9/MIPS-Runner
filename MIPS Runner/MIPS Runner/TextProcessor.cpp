#include "TextProcessor.h"

bool TextProcessor::isIgnoreCharacter(char c) {
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

//Remember to delete elements in tokenList.
void TextProcessor::extractToken(char* line, TokenList& tokenList) {
	int i = 0;
	while (line[i] != 0) {
		if (!isIgnoreCharacter(line[i])) {
			int run = i;
			while (!isIgnoreCharacter(line[run])) {
				++run;
			}

			char* token = new char[run - i + 1];
			for (int j = 0; j < run - i; ++j) {
				token[j] = line[i + j];
			}
			token[run - i] = 0;
			tokenList.pushBack(token);
			i = run;
			delete[] token;
		}
		else
			++i;
	}

}

Instruction* TextProcessor::parseTextToInstruction(char* line) {
	Instruction* instruction = nullptr;	
	
	TokenList tokenList;
	extractToken(line, tokenList);

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


void TextProcessor::parseSourceToInstruction(Instruction**& instructionList, int& numberOfInstruction) {
	// Count the number of instructions and allocate memory for them.
	numberOfInstruction = 0;
	for (int i = 0; i < numberOfCharacter; ++i) 
		if (sourceCode[i] == '\n')
			++numberOfInstruction;
	instructionList = new Instruction*[numberOfInstruction];

	//  Extract line from source code to parse it.
	char* line = new char[MAX_LINE_LENGTH];
	int begin = 0;
	int instructionCount = 0;
	for (int i = 0; i < numberOfCharacter; ++i) 
		if (sourceCode[i] == '\n') {
			for (int j = 0; j < i - begin; ++j) 
				line[j] = sourceCode[begin + j];
			line[i - begin] = 0;

			instructionList[instructionCount] = parseTextToInstruction(line);
			if (instructionList[instructionCount])
				++instructionCount;

			begin = i + 1;
		}
	numberOfInstruction = instructionCount;
	delete[] line;
}

// TODO: replace constant "source.mips" with dynamic file name.
void TextProcessor::readSourceFile() {
	std::ifstream inputFile("source.mips");
	
	inputFile.seekg(0, inputFile.end);
	numberOfCharacter = inputFile.tellg();
	inputFile.seekg(0, inputFile.beg);

	sourceCode = new char[numberOfCharacter + 2];

	int i = 0;
	while (!inputFile.eof()) {
		inputFile.getline(sourceCode + i, numberOfCharacter + 2);
		i += inputFile.gcount();
		if (sourceCode[i - 1] == 0) sourceCode[i - 1] = '\n';
	}

	numberOfCharacter = i + 1;
	sourceCode[numberOfCharacter - 1] = '\n';
	sourceCode[numberOfCharacter] = 0;

	for (int i = 0; i < numberOfCharacter; ++i)
		if (sourceCode[i] == ':') 
			sourceCode[i] = '\n';
	//std::cout << sourceCode;
}

TextProcessor::~TextProcessor() {
	delete[] sourceCode;
}