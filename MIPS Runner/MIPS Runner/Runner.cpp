#include "Runner.h"

Runner::~Runner() {
	for (int i = 0; i < numberOfLine; ++i) {
		delete[] file[i];
	}
	delete[] file;
}

Instruction* Runner::parseTextToInstruction(char* text) {
	
}

void Runner::parseSourceToInstruction() {
	for (int i = 0; i < numberOfLine; ++i) {
		instructionList[i] = parseTextToInstruction(file[i]);
	}
}

void Runner::readSourceFile() {
	std::ifstream inputFile("source.mips");

	file = new char* [50];
	numberOfLine = 0; 
	int i = 0;
	while (!inputFile.eof()) {
		file[i] = new char[50];
		inputFile.getline(file[i], 50);
		++i;
	}
	numberOfLine = i;

}

int main() {
	Runner runner;
	runner.readSourceFile();
}