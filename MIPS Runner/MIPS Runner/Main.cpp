#include "TextProcessor.h"
#include "Processor.h"

int main() {
	TextProcessor textProcessor;
	textProcessor.readSourceFile();

	int numberOfInstruction = 0;
	Instruction** instructionList = nullptr;
	textProcessor.parseSourceToInstruction(instructionList, numberOfInstruction);
	
	Processor processor(instructionList, numberOfInstruction);
	processor.run();
}