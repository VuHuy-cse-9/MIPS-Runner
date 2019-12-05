#include "ZeroArgInstruction.h"

// fuck error, big change awaiting.
ZeroArgInstruction::ZeroArgInstruction(TokenList& tokenList) 
: address((int*)LabelManager::getInstance()->addInstructionLabel(tokenList[0]), 0) {
}

void ZeroArgInstruction::execute() {
	InstructionOperand pc("$pc");
	*(address.memoryPtr) = *(pc.memoryPtr) + 1;
}