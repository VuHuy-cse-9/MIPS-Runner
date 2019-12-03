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

void OneArgInstruction::j(Register& address) {
	Register pc("$pc");
	pc = address;
}

void OneArgInstruction::jal(Register& address) {
	Register pc("$pc");
	Register ra("$ra");
	ra = pc;
	ra.advance(1);
	pc = address;
}