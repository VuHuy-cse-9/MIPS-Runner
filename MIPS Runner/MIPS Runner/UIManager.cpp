#include "UIManager.h"

const int UIManager::WALL_SIZE = 100;
const int UIManager::NUMBER_OF_RUNNING_LINE_SHOW = 10;
const int UIManager::NUMBER_OF_VARIABLE_LINE_SHOW = 30;


void UIManager::printWall(const char* header) {
	int headerSize = strlen(header);
	for (int i = 0; i < (WALL_SIZE - headerSize) / 2; ++i)
		std::cout << '-';
	std::cout << header;
	for (int i = 0; i < (WALL_SIZE - headerSize + 1) / 2; ++i)
		std::cout << '-';
	std::cout << '\n';
}

void UIManager::clearScreen() {
	system("cls");
}

void UIManager::printCompileErrorMessage(const char* message) {
	clearScreen();
	printSoureCode();
	printWall("COMPILE ERROR");
	std::cout << message << '\n';
	printWall("");
}

void UIManager::printRegisterData() {
	clearScreen();
	printWall("REGISTER");

	MemoryManager* memoryManager = MemoryManager::getInstance();
	for (int i = 0; i < MemoryManager::REGISTER_MEMORY_SIZE; ++i) {
		std::cout << MemoryManager::REGISTER_BASIC_NAME[i] << '\t';
		std::cout << MemoryManager::REGISTER_NAME[i] << '\t';
		std::cout << *memoryManager->getRegister(MemoryManager::REGISTER_NAME[i]) << '\n';
	}

	printWall("");
}

void UIManager::printVariableData() {
	clearScreen();
	printWall("VARIABLE");

	MemoryManager* memoryManager = MemoryManager::getInstance();
	for (int i = 0; i < NUMBER_OF_VARIABLE_LINE_SHOW; ++i) {
		for (int j = 0; j < WALL_SIZE / 4; ++j)
		{
			int val = memoryManager->variableMemory[i * WALL_SIZE / 4 + j];
			std::cout << val << std::setfill(' ') << std::setw(4);
		}
		std::cout << '\n';
	}

	printWall("");
}

void UIManager::printSoureCode() {
	clearScreen();
	TextProcessor* textProcessor = TextProcessor::getInstance();
	printWall("SOURCE CODE");

	int i = 0;
	int lineCount = 1;
	std::cout << lineCount << ":\t\t";
	while (textProcessor->sourceCode[i]) {
		std::cout << textProcessor->sourceCode[i];
		if (textProcessor->sourceCode[i] == '\n' && textProcessor->sourceCode[i + 1])
			std::cout << ++lineCount << ":\t\t";
		++i;
	}

	printWall("");
}

void UIManager::printRunningCode() {
	TextProcessor* textProcessor = TextProcessor::getInstance();
	InstructionOperand pc("$pc");

	clearScreen();
	printWall("RUNNING");

	int lineCurrent = *pc.memoryPtr + textProcessor->textSegmentBeginLine;
	int lineBegin = lineCurrent - NUMBER_OF_RUNNING_LINE_SHOW / 2;
	if (lineBegin < textProcessor->textSegmentBeginLine)
		lineBegin = textProcessor->textSegmentBeginLine;
	int lineEnd = lineCurrent + (NUMBER_OF_RUNNING_LINE_SHOW + 1) / 2;
	if (lineEnd > textProcessor->lineCount)
		lineEnd = textProcessor->lineCount;

	int i = 0, c = 0;
	while (c < lineBegin) {
		if (textProcessor->sourceCode[i] == '\n') ++c;
		++i;
	}
	int lineIndex = lineBegin;
	if (lineIndex == lineCurrent)
		std::cout << "-> " << std::to_string(lineIndex) << ":\t\t";
	else
		std::cout << "   " << std::to_string(lineIndex) << ":\t\t";

	while (lineIndex < lineEnd) {
		std::cout << textProcessor->sourceCode[i];
		if (textProcessor->sourceCode[i] == '\n') {
			++lineIndex;
			if (lineIndex < lineEnd)
				if (lineIndex == lineCurrent)
					std::cout << "-> " << std::to_string(lineIndex) << ":\t\t";
				else
					std::cout << "   " << std::to_string(lineIndex) << ":\t\t";
		}
		++i;
	}
	printWall("");
}

void UIManager::pauseAndWaitInput(const char* waitInput) {
	do {
		std::string input;
		std::cin >> input;

		if (input.compare(waitInput) == 0)
			break;
	} while (true);
}

void UIManager::run() {
	TextProcessor* textProcessor = TextProcessor::getInstance();
	Processor* processor = Processor::getInstance();

	textProcessor->readSourceFile();
	textProcessor->parseSourceToInstruction(processor->instructionList, processor->instructionListSize);

	printSoureCode();
	do {
		std::string input;
		std::cin >> input;

		if (input.compare("next") == 0 || input.compare("n") == 0) {
			if (processor->programEnded())
				break;
			processor->runNextInstruction();
			printRunningCode();
		}

		if (input.compare("all") == 0 || input.compare("a") == 0) {
			processor->run();
			break;
		}

		if (input.compare("source") == 0 || input.compare("s") == 0) {
			printSoureCode();
		}

		if (input.compare("running") == 0 || input.compare("u") == 0) {
			printRunningCode();
		}
		
		if (input.compare("register") == 0 || input.compare("r") == 0)
			printRegisterData();

		if (input.compare("variable") == 0 || input.compare("v") == 0)
			printVariableData();
	} while (true);

	printRegisterData();
}