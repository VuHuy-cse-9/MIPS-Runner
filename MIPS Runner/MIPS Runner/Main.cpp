#include "TextProcessor.h"
#include "ThreeArgInstruction.h"

int main() {
	TextProcessor textProcessor;
	textProcessor.readSourceFile();

	int numberOfInstruction = 0;
	Instruction** instructionList = nullptr;
	textProcessor.parseSourceToInstruction(instructionList, numberOfInstruction);

	for (int i = 0; i < numberOfInstruction; ++i)
		instructionList[i]->execute();
	return 0;
}