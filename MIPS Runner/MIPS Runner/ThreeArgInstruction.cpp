#include "ThreeArgInstruction.h"

ThreeArgInstruction::ThreeArgInstruction(TokenList& tokenList)
	: rd(tokenList[1]), rs(tokenList[2]), rt(tokenList[3]) {

	function = nullptr;
//we neeed 3 three instruction here
	if (strcmp(tokenList[0], "add") == 0) this->function = add;
	if (strcmp(tokenList[0], "sub") == 0) this->function = sub;
	if (strcmp(tokenList[0], "mul") == 0) this->function = mul;
	if (strcmp(tokenList[0], "addu") == 0) this->function = addu;
	if (strcmp(tokenList[0], "subu") == 0) this->function = subu;
	if (strcmp(tokenList[0], "slt") == 0) this->function = slt;
	if (strcmp(tokenList[0], "or") == 0) this->function = Or;
	if (strcmp(tokenList[0], "and") == 0) this->function = And;

//separate i for what?we need 2 instruction and 1 literal
	if (strcmp(tokenList[0], "addi") == 0)this->function = add;
	if (strcmp(tokenList[0], "addiu") == 0) this->function = addu;
	if (strcmp(tokenList[0], "subiu") == 0) this->function = sub;
	if (strcmp(tokenList[0], "andi") == 0) this->function = And;
	if (strcmp(tokenList[0], "ori") == 0) this->function = Or;
	if (strcmp(tokenList[0], "sll") == 0) this->function = sll;
	if (strcmp(tokenList[0], "srl") == 0) this->function = srl;
	if (strcmp(tokenList[0], "subi") == 0) this->function = sub;
	if (strcmp(tokenList[0], "slti") == 0) this->function = slt;
	
	if (strcmp(tokenList[0], "beq") == 0) this->function = beq;
	if (strcmp(tokenList[0], "bne") == 0) this->function = bne;
} 

void ThreeArgInstruction::execute() {
	if (function)
		function(this->rd, this->rs, this->rt);
}

void ThreeArgInstruction::add(Register& rd, Register& rs, Register& rt) {
	rd = rs + rt;
}

void ThreeArgInstruction::addu(Register& rd, Register& rs, Register& rt) { // 
	rd = rs.addUnsigned(rt);
}

void ThreeArgInstruction::sub(Register& rd, Register& rs, Register& rt) {
	rd = rs - rt;
}

void ThreeArgInstruction::subu(Register& rd, Register& rs, Register& rt) { // 
	rd = rs.subtractUnsigned(rt);
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

//problem with this function
void ThreeArgInstruction::beq(Register& rd, Register& rs, Register& rt) {
	Register pc("$pc");
	if (rd == rs)
		pc = rt;
}

void ThreeArgInstruction::bne(Register& rd, Register& rs, Register& rt) {
	Register pc("$pc");
	if (rd != rs)
		pc = rt;
}

