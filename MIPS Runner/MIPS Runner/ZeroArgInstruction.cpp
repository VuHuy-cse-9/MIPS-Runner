#include "ZeroArgInstruction.h"

// fuck error, big change awaiting.
ZeroArgInstruction::ZeroArgInstruction(TokenList& tokenList) 
: address(LabelManager::addLabel(tokenList[0], 4, 0)) {
}

void ZeroArgInstruction::execute() {
	Register pc("$pc");
	address = pc;
	address.advance(1);
}