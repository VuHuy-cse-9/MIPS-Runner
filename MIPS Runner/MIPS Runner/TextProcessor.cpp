#include "TextProcessor.h"

SmartPointer<TextProcessor> TextProcessor::instance = nullptr;

TextProcessor::TextProcessor() {
	sourceCode = nullptr;
	sourceCodeSize = 0;
	lineCount = 0;
	textSegmentBeginLine = 0;

	src = nullptr;
}

TextProcessor::~TextProcessor() {
	delete[] sourceCode;
	for (int i = 0; src[i]; ++i)
		delete[] src[i];
	delete[] src;
}

TextProcessor* TextProcessor::getInstance() {
	if (!instance)
		instance = new TextProcessor;
	return instance;
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

int TextProcessor::countLine(const char* source) {
	if (!*source)
		return 0;

	int count = 1;
	for (int i = 0; source[i]; ++i)
		count += (source[i] == '\n');
	return count;
}

void TextProcessor::markComment(char*& line) {
	for (int i = 0; line[i]; ++i)
		if (line[i] == '#') {
			line[i] = '\0';
			break;
		}
}

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

char** TextProcessor::processData(char** src) {
	char** currentLine = src;
	while (*currentLine) {
		++currentLine;
		if (strcmp(*(currentLine - 1), ".data") == 0) break;
	}

	while (*currentLine) 
		if (strcmp(*currentLine, ".text") != 0) {
			try {
				DataAnalyse execute(*currentLine);
			}
			catch (std::string message) {
				throw std::string("line ") + std::to_string(currentLine - src) + std::string(":\t\t") + message;
			}
			++currentLine;
		}
		else break;

	return currentLine;
}

void TextProcessor::processLabel(char** currentLine, Instruction**& instructionList) {
	int index = -1;
	while (*currentLine) {
		TokenList tokenList(*currentLine);
		++currentLine;
		++index;

		if (tokenList.size() != 1) continue;
		if (strcmp(tokenList[0], "syscall") == 0) continue;

		try {
			Instruction* instruction = new ZeroArgInstruction(tokenList);
			InstructionOperand pc("$pc");
			*pc.memoryPtr = (currentLine - src) - textSegmentBeginLine - 2;
			instruction->execute();
			instructionList[index] = instruction;
		}
		catch (std::string message) {
			throw std::string("line ") + std::to_string(currentLine - src) + std::string(":\t\t") + message;
		}
	}
}

void TextProcessor::processInstruction(char** currentLine, Instruction**& instructionList, int& instructionListSize) {
	int index = -1;
	while (*currentLine) {
		TokenList tokenList(*currentLine);
		++currentLine;
		++index;

		if (tokenList.size() == 1 && strcmp(tokenList[0], "syscall") != 0) continue;
		try {
			instructionList[index] = parseLineToInstruction(*(currentLine - 1));
		}
		catch (std::string message) {
			throw std::string("line ") + std::to_string(currentLine - src) + std::string(":\t\t") + message;
		}
	}
	instructionListSize = index + 1;
}

void TextProcessor::parseSourceToInstruction(Instruction**& _instructionList, int& _instructionListSize) {
	_instructionList = new Instruction * [countLine(sourceCode)];
	
	// *currentLine = ".text"
	char** currentLine = processData(src);
	textSegmentBeginLine = currentLine - src;
	processLabel(currentLine + 1, _instructionList);
	processInstruction(currentLine + 1, _instructionList, _instructionListSize);
}

bool TextProcessor::extractLabel(char*& destination, char*& source) {
	do
	{
		bool isLabel = false;
		bool inQuote = false;
		int i;
		for (i = 0; source[i]; ++i) {
			if (source[i] == ':' && !inQuote) {
				isLabel = true;

				break;
			}

			if (source[i] == '\"') 
				inQuote = !inQuote;
		}
		if (!isLabel) break;

		char* newLineBegin = source + i + 1;
		while (isSpacing(*source)) ++source, --i;
		while (isSpacing(source[i - 1])) --i;

		for (int j = 0; j < i; ++j)
			*(destination++) = source[j];
		*(destination++) = ':';
		*(destination++) = '\n';

		source = newLineBegin;
	} while (true);

	return isEmptyLine(source);
}

bool TextProcessor::extractOpCode(char*& destination, char*& source) {
	while (isSpacing(*source)) ++source;
	if (!*source) return true;

	while (!isSpacing(*source) && *source)
		*(destination++) = *(source++);
	if (isEmptyLine(source)) {
		*(destination++) = '\n';
		return true;
	}

	*(destination++) = ' ';
	return false;
}

bool TextProcessor::extractArgument(char*& destination, char*& source) {
	do
	{
		while (isSpacing(*source)) ++source;
		while (*source != ',' && *source)
			*(destination++) = *(source++);
		while (isSpacing(*(destination - 1))) destination--;

		if (isEmptyLine(source)) {
			*(destination++) = '\n';
			return false;
		}
		*(destination++) = *(source++);
	} while (true);

}

void TextProcessor::standarize(char*& line) {
	markComment(line);
	if (isEmptyLine(line)) {
		line[0] = 0;
		return;
	}
	
	char* formatedLine = new char[MAX_LINE_LENGTH];
	char* currentFormatedLine = formatedLine;
	char* currentLine = line;

	if (extractLabel(currentFormatedLine, currentLine)) {
		delete[] line;
		*(currentFormatedLine++) = '\0';
		line = formatedLine;
		return;
	}

	if (extractOpCode(currentFormatedLine, currentLine)) {
		delete[] line;
		*(currentFormatedLine++) = '\0';
		line = formatedLine;
		return;
	}

	extractArgument(currentFormatedLine, currentLine);
	delete[] line;
	*(currentFormatedLine++) = '\0';
	line = formatedLine;
	return;
}

void TextProcessor::standarize() {
	// the end of formatedSourceCode contain "\n\0".

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

	src = new char* [countLine(sourceCode) + 1];
	src[0] = nullptr;

	int index = 0;
	char* beginLine = sourceCode;
	while (*beginLine) {
		char* endLine = lineEnd(beginLine);

		src[index] = new char[endLine - beginLine + 1];
		src[index][endLine - beginLine] = '\0';
		for (int i = 0; beginLine + i != endLine; ++i)
			src[index][i] = beginLine[i];

		++index;
		src[index] = nullptr;
		beginLine = endLine + 1;
	}
}


// TODO: replace constant "source.mips" with dynamic file name.
void TextProcessor::readSourceFile() {
	std::ifstream inputFile("source.txt");
	
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

	standarize();
}