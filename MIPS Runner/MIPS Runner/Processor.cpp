#include "Processor.h"

Processor::Processor(Instruction**& _instructionList, const int& _instructionListSize) 
: instructionList(_instructionList), instructionListSize(_instructionListSize), pc("$pc") {
}

int Processor::runNextInstruction() {
	instructionList[*pc.memoryPtr]->execute();
	++* pc.memoryPtr;
	return 0;
}

int Processor::run() { // 0 => no bugs,1 bugs // run all code 
	// have 1 instructionlist;
	// no chay chuong trinh
	while (*pc.memoryPtr < instructionListSize) {
		int exitcode = runNextInstruction();
		if (exitcode != 0) return exitcode;
	}
	return 0;
}



