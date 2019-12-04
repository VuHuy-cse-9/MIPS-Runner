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


void TwoArgInstruction::mult(Register& rs, Register& rt) {
	rs.mult(rt);
}

void TwoArgInstruction::div(Register& rs, Register& rt) {
	rs.div(rt);
}

void TwoArgInstruction::lui(Register& rs, Register& rt) {
	rs = rt.lui(16);
}

void TwoArgInstruction::move(Register& rs, Register& rt) {
	rs = rt;
}

void TwoArgInstruction::lw(Register& rs, Register& rt ) {
	rs = rt;
}