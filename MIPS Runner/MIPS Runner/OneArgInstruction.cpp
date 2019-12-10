#include "OneArgInstruction.h"

OneArgInstruction::OneArgInstruction(TokenList& tokenList) 
	: address(tokenList[1]) {
	function = nullptr;

	if (strcmp("j", tokenList[0]) == 0) function = j;
	if (strcmp("jr", tokenList[0]) == 0) function = j;
	if (strcmp("jal", tokenList[0]) == 0) function = jal;
	if (strcmp("bc1f", tokenList[0]) == 0) function = bc1f;
	if (strcmp("bc1t", tokenList[0]) == 0) function = bc1t;

	
	if (!function)
		throw std::string("cannot resolve \"") + std::string(tokenList[0]) + std::string("\"");
	if (!address.signatureIs("Ii") && !address.signatureIs("Li"))
		throw std::string("\"") + std::string(tokenList[1]) + std::string("\" have to be an instruction label or an integer");
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
	*(pc.memoryPtr) = *(address.memoryPtr);
}

void OneArgInstruction::bc1f(InstructionOperand& address) {
	InstructionOperand $32("$32");
	InstructionOperand pc("$pc");
	if(*((double*)$32.memoryPtr) == 0)*(pc.memoryPtr) = *(address.memoryPtr);
}

void OneArgInstruction::bc1t(InstructionOperand& address) {
	InstructionOperand $32("$32");
	InstructionOperand pc("$pc");
	if (*((double*)$32.memoryPtr) == 1)*(pc.memoryPtr) = *(address.memoryPtr);
}