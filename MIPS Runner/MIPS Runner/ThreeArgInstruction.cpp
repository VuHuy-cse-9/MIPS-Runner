#include "ThreeArgInstruction.h"

const char* ThreeArgInstruction::THREE_ARG_INSTRUCTION_LIST[] = { "add", "sub", "and", "or" };
const int ThreeArgInstruction::THREE_ARG_INSTRUCTION_LIST_SIZE = 4;

ThreeArgInstruction::ThreeArgInstruction(const char* line) {
	// Get line size;
	int lineSize = 0;
	while (line[lineSize] != 0) {
		++lineSize;
	}

	// Extract command from line.
	char* command = new char[5];
	int i = 0;
	while (line[i] != ' ') {
		command[i] = line[i];
		++i;
	}

	// get register name from line.
	char** registerName = new char* [3];
	for (int i = 0; i < 3; ++i) {
		registerName[i] = new char[5];
	}
	int k = 0;
	for (int begin = i; begin < lineSize; begin++) {
		if (line[begin] == '$') {
			for (int j = begin; j < lineSize; ++j) {
				if (line[j] != ' ' && line[j] != ',' && line[j] != 0) {
					registerName[k][j - begin] = line[j];
				}
			}
			++k;
		}
	}

	std::cout << command << '\n';
	for (int i = 0; i < 3; ++i)
		std::cout << registerName[i] << '\n';

	delete[] command;
	for (int i = 0; i < 3; ++i)
		delete[] registerName[i];
	delete[] registerName;
}

void ThreeArgInstruction::execute() {
	function(this->rd, this->rs, this->rt);
}