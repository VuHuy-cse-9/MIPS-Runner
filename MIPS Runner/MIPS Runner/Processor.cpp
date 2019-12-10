#include "Processor.h"

SmartPointer<Processor> Processor::instance = nullptr;

Processor::Processor() 
	: pc("$pc") {
	instructionList = nullptr;
	instructionListSize = 0;
	*pc.memoryPtr = 0;
}

Processor* Processor::getInstance() {
	if (!instance) 
		instance = new Processor;
	return instance;
}

void Processor::prepare() {
	*pc.memoryPtr = 0;
}

int Processor::runNextInstruction() {
	instructionList[*pc.memoryPtr]->execute();
	++(*pc.memoryPtr);
	return 0;
}

int Processor::run() { // 0 => no bugs,1 bugs // run all code 
	// have 1 instructionlist;
	// no chay chuong trinh
	
	try {
		while (*pc.memoryPtr < instructionListSize) {
			int exitcode = runNextInstruction();
			if (exitcode != 0) return exitcode;
		}
	}
	// catch exitcode from syscall.
	catch (int exitcode) {
		return exitcode;
	}

	return 0;
}

bool Processor::programEnded() {
	return (*pc.memoryPtr == instructionListSize);
}

