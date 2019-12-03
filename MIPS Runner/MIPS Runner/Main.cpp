#include "TextProcessor.h"
#include "Processor.h"

int main() {
	TextProcessor textProcessor;
	textProcessor.readSourceFile();

	int instructionListSize = 0;
	Instruction** instructionList = nullptr;
	textProcessor.parseSourceToInstruction(instructionList, instructionListSize);
	
	Processor processor(instructionList, instructionListSize);
	processor.run();
}