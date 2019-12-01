#include "ThreeArgInstruction.h"

const char* ThreeArgInstruction::THREE_ARG_INSTRUCTION_LIST[] = { "add", "sub", "and", "or", "sll", "srl" };
const int ThreeArgInstruction::THREE_ARG_INSTRUCTION_LIST_SIZE = 4;

ThreeArgInstruction::ThreeArgInstruction(TokenList& listOfToken)
	: rd(listOfToken[1]), rs(listOfToken[2]), rt(listOfToken[3]) {
	if (strcmp(listOfToken[0], "add") == 0) this->function = add;
	//if (strcmp(listOfToken[0], "addi") == 0)this->function = add;
	if (strcmp(listOfToken[0], "sub") == 0) this->function = sub;
	if (strcmp(listOfToken[0], "and") == 0) this->function = And;
	if (strcmp(listOfToken[0], "or") == 0) this->function = Or;
	if (strcmp(listOfToken[0], "sll") == 0) this->function = sll;
	if (strcmp(listOfToken[0], "srl") == 0) this->function = srl;
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

void ThreeArgInstruction::sll(Register rd, Register rs, Register rt) {
	rd = rs << rt;
}

void ThreeArgInstruction::sll(Register rd, Register rs, Register rt) {
	rd = rs >> rt;
}