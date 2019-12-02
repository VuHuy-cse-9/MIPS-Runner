#include "OneArgInstruction.h"

OneArgInstruction::OneArgInstruction(TokenList& ListOfToken) 
	:rd(ListOfToken[1]) {
	function = nullptr;
	if (strcmp("j", ListOfToken[0]) == 0) function = j;
	if (strcmp("jr", ListOfToken[0]) == 0) function = j;
	if (strcmp("jal", ListOfToken[0]) == 0) function = jal;
}

void OneArgInstruction::execute() {
	if (function)
		function(rd);
}

void OneArgInstruction::j(Register& rd) {
	Register pc("$pc");
	pc = rd;
}

void OneArgInstruction::jal(Register& rd) {
	Register pc("$pc");
	Register ra("$ra");
	ra = pc;
	ra.advance(1);
	pc = rd;
}