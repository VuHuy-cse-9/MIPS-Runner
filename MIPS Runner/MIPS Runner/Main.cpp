#include <iostream>
#include <string>

#include "TextProcessor.h"
#include "Processor.h"

int main() {
	TextProcessor textProcessor;
	textProcessor.readSourceFile();
	textProcessor.printSourceCode();

	try {
		int instructionListSize = 0;
		Instruction** instructionList = nullptr;
		textProcessor.parseSourceToInstruction(instructionList, instructionListSize);

		Processor processor(instructionList, instructionListSize);
		processor.run();
	}
	catch (std::string message) {
		std::cout << "----------------------------------ERROR-----------------------------------\n";
		std::cout << message << '\n';
		std::cout << "--------------------------------------------------------------------------\n";
	}
}