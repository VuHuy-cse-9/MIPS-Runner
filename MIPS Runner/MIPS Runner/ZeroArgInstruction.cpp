#include "ZeroArgInstruction.h"

// fuck error, big change awaiting.
ZeroArgInstruction::ZeroArgInstruction(TokenList& tokenList) 
: address(LabelManager::getInstance()->addInstructionLabel(tokenList[0])) {
}

void ZeroArgInstruction::execute() {
	Register pc("$pc");
	address = pc;
	address.advance(1);
}