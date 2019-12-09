#include "TwoArgInstruction.h"

TwoArgInstruction::TwoArgInstruction(TokenList& tokenList) :
	rs( tokenList[1]),rt(tokenList[2]) {
	if (!rs.signatureIs("Rb"))
		throw std::string("\"") + std::string(tokenList[1]) + std::string("\" have to be a register");

	function = nullptr;
	if (strcmp(tokenList[0], "mult") == 0) this->function = mult;
	if (strcmp(tokenList[0], "div") == 0) this->function = div;
	if (function)
		if (!rt.signatureIs("Rb"))
			throw std::string("\"") + std::string(tokenList[2]) + std::string("\" have to be a register");
		else
			return;

	if (strcmp(tokenList[0], "lui") == 0) this->function = lui;
	if (strcmp(tokenList[0], "li") == 0) this->function = move;
	if (function)
		if (!rt.signatureIs("Ii"))
			throw std::string("\"") + std::string(tokenList[2]) + std::string("\" have to be an integer");
		else
			return;
	
	if (strcmp(tokenList[0], "la") == 0) this->function = la;
	if (function)
		if (!rt.signatureIs("Lv"))
			throw std::string("\"") + std::string(tokenList[2]) + std::string("\" have to be a variable label");
		else
			return;

	if (strcmp(tokenList[0], "sw") == 0) this->function = sw;
	if (strcmp(tokenList[0], "lw") == 0) this->function = lw;
	if (function)
		if (!rt.signatureIs("Rw") && !rt.signatureIs("Lv"))
			throw std::string("\"") + std::string(tokenList[2]) + std::string("\" have to be an eclosed register \"offset(register name)\"");
		else
			return;

	if (strcmp(tokenList[0], "move") == 0) this->function = move;	
	if (function)
		if (!rt.signatureIs("Rb") || rt.signatureIs("Lv"))
			throw std::string("\"") + std::string(tokenList[2]) + std::string("\" have to be a register or a variable label");
		else
			return;

	if (!function)
		throw std::string("cannot resolve \"") + std::string(tokenList[0]) + std::string("\"");
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

void TwoArgInstruction::sw(InstructionOperand& rs, InstructionOperand& rt) {
	*(rt.memoryPtr + rt.offset) = *rs.memoryPtr;
}

void TwoArgInstruction::lw(InstructionOperand& rs, InstructionOperand& rt) {
	*(rs.memoryPtr) = *(rt.memoryPtr + rt.offset);
}

void TwoArgInstruction::la(InstructionOperand& rs, InstructionOperand& rt) {
	*(rs.memoryPtr) = (int) rt.memoryPtr;
}
