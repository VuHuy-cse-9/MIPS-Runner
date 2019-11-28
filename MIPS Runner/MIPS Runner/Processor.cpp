#include "Processor.h"

// TODO: replace constant "source.mips" with dynamic file name.
void Processor::readSourceFile() {
	std::ifstream inputFile("source.mips");
	
	inputFile.seekg(0, inputFile.end);
	numberOfCharacter = inputFile.tellg();
	inputFile.seekg(0, inputFile.beg);

	sourceCode = new char[numberOfCharacter + 1];

	int i = 0;
	while (!inputFile.eof()) {
		inputFile.getline(sourceCode + i, numberOfCharacter);
		i += inputFile.gcount();
		sourceCode[i - 1] = '\n';
	}

	numberOfCharacter = i;
	sourceCode[numberOfCharacter] = 0;


	for (int i = 0; i < numberOfCharacter; ++i)
		if (sourceCode[i] == ':') 
			sourceCode[i] = '\n';
	std::cout << sourceCode;
}

Instruction* Processor::parseTextToInstruction(char* line) {
	char* command = new char[MAX_LINE_LENGTH];
	int i = 0;
	while (line[i] != ' ' && line[i] != 0) {
		command[i] = line[i];
		++i;
	}
	command[i] = 0;
	
	for (int i = 0; i < R_Instruction::R_INSTRUCTION_LIST_SIZE; ++i)
		if (strcmp(command, R_Instruction::R_INSTRUCTION_LIST[i]) == 0) {
			// create new R_Instruction.
		}

	delete[] command;

}

void Processor::parseSourceToInstruction() {
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
			++instructionCount;
			begin = i + 1;
		}
	
	delete[] line;
}

Processor::~Processor() {
	delete[] sourceCode;
}