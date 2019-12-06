#include <iostream>
#include <string>
#include "DataAnalyse.h"

#include "TextProcessor.h"
#include "Processor.h"

int main() {
	try {
		TextProcessor textProcessor;
		textProcessor.readSourceFile();

		int instructionListSize = 0;
		Instruction** instructionList = nullptr;
		textProcessor.parseSourceToInstruction(instructionList, instructionListSize);

		Processor processor(instructionList, instructionListSize);
		processor.run();
	}
	catch (std::string message) {
		std::cout << "--------------------------------------------------------------------------\n";
		std::cout << "ERROR: ";
		std::cout << message << '\n';
		std::cout << "--------------------------------------------------------------------------\n";
	}
}