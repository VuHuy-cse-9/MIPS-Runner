#include "ThreeArgInstruction.h"

const char* ThreeArgInstruction::THREE_ARG_INSTRUCTION_LIST[] = { "add", "sub", "and", "or" };
const int ThreeArgInstruction::THREE_ARG_INSTRUCTION_LIST_SIZE = 4;

ThreeArgInstruction::ThreeArgInstruction(TokenList& listOfToken)
	: rd(listOfToken[1]), rs(listOfToken[2]), rt(listOfToken[3]) {
	if (strcmp(listOfToken[0], "add") == 0) this->function = add;
	if (strcmp(listOfToken[0], "sub") == 0) this->function = sub;
} 

void ThreeArgInstruction::execute() {
	function(this->rd, this->rs, this->rt);
}

void ThreeArgInstruction::add(Register rd, Register rs, Register rt) {
	rd = rs + rt;
}

void ThreeArgInstruction::sub(Register rd, Register rs, Register rt) {
	rd = rs - rt;
}

void ThreeArgInstruction::And(Register rd, Register rs, Register rt) {
	rd = rs & rt;
}

void ThreeArgInstruction::Or(Register rd, Register rs, Register rt) {
	rd = rs | rt;
}
