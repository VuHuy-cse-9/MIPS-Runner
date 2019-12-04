#include "OneArgInstruction.h"

OneArgInstruction::OneArgInstruction(TokenList& tokenList) 
	: address(tokenList[1]) {
	function = nullptr;
	if (strcmp("j", tokenList[0]) == 0) function = j;
	if (strcmp("jr", tokenList[0]) == 0) function = j;
	if (strcmp("jal", tokenList[0]) == 0) function = jal;
}

void OneArgInstruction::execute() {
	if (function)
		function(address);
}

void OneArgInstruction::j(InstructionOperand& address) {
	InstructionOperand pc("$pc");
	*(pc.memoryPtr) = *(address.memoryPtr);
}

void OneArgInstruction::jal(InstructionOperand& address) {
	InstructionOperand pc("$pc");
	InstructionOperand ra("$ra");
	*(ra.memoryPtr) = *(pc.memoryPtr);
	*(ra.memoryPtr) += 1;
	*(pc.memoryPtr) = *(address.memoryPtr);
}