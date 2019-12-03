#include "TwoArgInstruction.h"

TwoArgInstruction::TwoArgInstruction(TokenList& listOfToken) :
	rs( listOfToken[1]),rt(listOfToken[2]) {
	function = nullptr;
	if (strcmp(listOfToken[0], "mult") == 0) this->function = mult;
	if (strcmp(listOfToken[0], "div") == 0) this->function = div;
	if (strcmp(listOfToken[0], "move") == 0) this->function = move;
	if (strcmp(listOfToken[0], "lui") == 0) this->function = lui;
	if (strcmp(listOfToken[0], "li") == 0) this->function = move;
}

void TwoArgInstruction::execute() {
	if (function)
		function(this->rs, this->rt);
}

//Todo here
void* TwoArgInstruction::getArray(const char* token) {
	
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