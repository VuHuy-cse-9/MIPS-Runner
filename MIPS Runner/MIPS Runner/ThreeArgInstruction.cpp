#include "ThreeArgInstruction.h"

const char* ThreeArgInstruction::THREE_ARG_INSTRUCTION_LIST[] = { "add", "sub", "and", "or", "sll", "srl" };
const int ThreeArgInstruction::THREE_ARG_INSTRUCTION_LIST_SIZE = 4;

ThreeArgInstruction::ThreeArgInstruction(TokenList& listOfToken)
	: rd(listOfToken[1]), rs(listOfToken[2]), rt(listOfToken[3]) {
	function = nullptr;
	if (strcmp(listOfToken[0], "add") == 0) this->function = add;
	if (strcmp(listOfToken[0], "addi") == 0)this->function = add;
	if (strcmp(listOfToken[0], "addu") == 0) this->function = addu;
	if (strcmp(listOfToken[0], "addiu") == 0) this->function = addu;
	if (strcmp(listOfToken[0], "sub") == 0) this->function = sub;
	if (strcmp(listOfToken[0], "subi") == 0) this->function = sub;
	if (strcmp(listOfToken[0], "subu") == 0) this->function = subu;
	if (strcmp(listOfToken[0], "subiu") == 0) this->function = sub;
	if (strcmp(listOfToken[0], "and") == 0) this->function = And;
	if (strcmp(listOfToken[0], "andi") == 0) this->function = And;
	if (strcmp(listOfToken[0], "or") == 0) this->function = Or;
	if (strcmp(listOfToken[0], "ori") == 0) this->function = Or;
	if (strcmp(listOfToken[0], "sll") == 0) this->function = sll;
	if (strcmp(listOfToken[0], "srl") == 0) this->function = srl;
	if (strcmp(listOfToken[0], "mul") == 0) this->function = mul;
	if (strcmp(listOfToken[0], "slt") == 0) this->function = slt;
	if (strcmp(listOfToken[0], "slti") == 0) this->function = slt;
	//rd.getRegister();
} 

void ThreeArgInstruction::execute() {
	if (function)
		function(this->rd, this->rs, this->rt);
}

void ThreeArgInstruction::add(Register& rd, Register& rs, Register& rt) {
	rd = rs + rt;
}

void ThreeArgInstruction::addu(Register& rd, Register& rs, Register& rt) { // 
	rd = rs.addu(rt);
}

void ThreeArgInstruction::sub(Register& rd, Register& rs, Register& rt) {
	rd = rs - rt;
}

void ThreeArgInstruction::subu(Register& rd, Register& rs, Register& rt) { // 
	rd = rs.subu(rt);
}

void ThreeArgInstruction::And(Register& rd, Register& rs, Register& rt) {
	rd = rs & rt;
}

void ThreeArgInstruction::Or(Register& rd, Register& rs, Register& rt) {
	rd = rs | rt;
}

void ThreeArgInstruction::sll(Register& rd, Register& rs, Register& rt) {
	rd = rs << rt;
}

void ThreeArgInstruction::srl(Register& rd, Register& rs, Register& rt) {
	rd = rs >> rt;
}

void ThreeArgInstruction::mul(Register& rd, Register& rs, Register& rt) {
	rd = rs * rt;
}

void ThreeArgInstruction::slt(Register& rd, Register& rs, Register& rt) {
	rd = rs < rt;
}
