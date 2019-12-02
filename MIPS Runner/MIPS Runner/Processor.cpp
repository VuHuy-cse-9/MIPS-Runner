#include "Processor.h"

Processor::Processor(Instruction**& _instructionList, const int& _numberOfStruction) 
: instructionList(_instructionList), numberOfInstruction(_numberOfStruction), pc("$pc") {
}

int Processor::runNextInstruction() {
	instructionList[pc.getValue()]->execute();
	pc.advance(1);
	return 0;
}

int Processor::run() { // 0 => no bugs,1 bugs // run all code 
	// have 1 instructionlist;
	// no chay chuong trinh
	while (pc.getValue() < numberOfInstruction) {
		int exitcode = runNextInstruction();
		if (exitcode != 0) return exitcode;
	}
	return 0;
}

//three argu, two argu



