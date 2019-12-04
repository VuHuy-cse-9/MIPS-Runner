#include "TwoArgInstruction.h"

TwoArgInstruction::TwoArgInstruction(TokenList& tokenList) :
	rs( tokenList[1]),rt(tokenList[2]) {
	function = nullptr;
	if (strcmp(tokenList[0], "mult") == 0) this->function = mult;
	if (strcmp(tokenList[0], "div") == 0) this->function = div;
	if (strcmp(tokenList[0], "move") == 0) this->function = move;
	if (strcmp(tokenList[0], "lui") == 0) this->function = lui;
	if (strcmp(tokenList[0], "li") == 0) this->function = move;
	if (strcmp(tokenList[0], "lw") == 0) this->function = lw;
}

void TwoArgInstruction::execute() {
	if (function)
		function(this->rs, this->rt);
}


void TwoArgInstruction::mult(InstructionOperand& rs, InstructionOperand& rt) {
	InstructionOperand hi("$hi");
	InstructionOperand lo("$lo");
	long long result = (long long) *(rs.memoryPtr) * (long long) * (rt.memoryPtr);
	long long* ptr = &result;
	*(hi.memoryPtr) = ((int*)ptr)[1];
	*(lo.memoryPtr) = ((int*)ptr)[0];
}

void TwoArgInstruction::div(InstructionOperand& rs, InstructionOperand& rt) {
	InstructionOperand hi("$hi");
	InstructionOperand lo("$lo");
	*(hi.memoryPtr) = *(rs.memoryPtr) % *(rt.memoryPtr);
	*(lo.memoryPtr) = *(rs.memoryPtr) / *(rt.memoryPtr);
}

void TwoArgInstruction::lui(InstructionOperand& rs, InstructionOperand& rt) {
	*(rs.memoryPtr) = *(rt.memoryPtr) << 16;
}

void TwoArgInstruction::move(InstructionOperand& rs, InstructionOperand& rt) {
	*(rs.memoryPtr) = *(rt.memoryPtr);
}

//Bug here
void TwoArgInstruction::lw(InstructionOperand& rs, InstructionOperand& rt) {
	*(rs.memoryPtr) = *(rt.memoryPtr);
}