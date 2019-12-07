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

	if (strcmp(tokenList[0], "addi") == 0)this->function = add;
	if (strcmp(tokenList[0], "addiu") == 0) this->function = addu;
	if (strcmp(tokenList[0], "subiu") == 0) this->function = sub;
	if (strcmp(tokenList[0], "andi") == 0) this->function = And;
	if (strcmp(tokenList[0], "ori") == 0) this->function = Or;
	if (strcmp(tokenList[0], "sll") == 0) this->function = sll;
	if (strcmp(tokenList[0], "srl") == 0) this->function = srl;
	if (strcmp(tokenList[0], "subi") == 0) this->function = sub;
	if (strcmp(tokenList[0], "slti") == 0) this->function = slt;
	
	if (strcmp(tokenList[0], "add.s") == 0) this->function = adds;
	if (strcmp(tokenList[0], "sub.s") == 0) this->function = subs;
	if (strcmp(tokenList[0], "mul.s") == 0) this->function = muls;
	if (strcmp(tokenList[0], "div.s") == 0) this->function = divs;
} 

void ThreeArgInstruction::execute() {
	if (function)
		function(this->rd, this->rs, this->rt);
}

void ThreeArgInstruction::add(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	*(rd.memoryPtr) = *(rs.memoryPtr) + *(rt.memoryPtr);
}

void ThreeArgInstruction::addu(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) { 
	*(rd.memoryPtr) = (unsigned int)*(rs.memoryPtr) + (unsigned int)*(rt.memoryPtr);
}

void ThreeArgInstruction::sub(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	*(rd.memoryPtr) = *(rs.memoryPtr) - *(rt.memoryPtr);
}

void ThreeArgInstruction::subu(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) { // 
	*(rd.memoryPtr) = (unsigned int) * (rs.memoryPtr) - (unsigned int) * (rt.memoryPtr);
}

void ThreeArgInstruction::And(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	*(rs.memoryPtr) = *(rs.memoryPtr) & *(rt.memoryPtr);
}

void ThreeArgInstruction::Or(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	*(rd.memoryPtr) = *(rs.memoryPtr) | *(rt.memoryPtr);
}

void ThreeArgInstruction::sll(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	*(rd.memoryPtr) = *(rs.memoryPtr) << *(rt.memoryPtr);
}

void ThreeArgInstruction::srl(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	*(rd.memoryPtr) = *(rs.memoryPtr) >> *(rt.memoryPtr);
}

void ThreeArgInstruction::mul(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	*(rd.memoryPtr) = *(rs.memoryPtr) * *(rt.memoryPtr);
}

void ThreeArgInstruction::slt(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	*(rd.memoryPtr) = *(rs.memoryPtr) < *(rt.memoryPtr);
}

void ThreeArgInstruction::beq(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	InstructionOperand pc("$pc");
	if (*(rd.memoryPtr) == *(rs.memoryPtr))
		*(pc.memoryPtr) = *(rt.memoryPtr);
}

void ThreeArgInstruction::bne(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	InstructionOperand pc("$pc");
	if (*(rd.memoryPtr) != *(rs.memoryPtr))
		*(pc.memoryPtr) = *(rt.memoryPtr);
}

void ThreeArgInstruction::adds(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	//*(rd.memoryPtr) = (float)*(rs.memoryPtr) + (*float)*(rt.memoryPtr)(*float);
}

void ThreeArgInstruction::subs(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	*(rd.memoryPtr) = *(rs.memoryPtr) >> *(rt.memoryPtr);
}

void ThreeArgInstruction::muls(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	*(rd.memoryPtr) = *(rs.memoryPtr) >> *(rt.memoryPtr);
}

void ThreeArgInstruction::divs(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	*(rd.memoryPtr) = *(rs.memoryPtr) >> *(rt.memoryPtr);
}



