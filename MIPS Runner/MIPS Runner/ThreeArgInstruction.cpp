#include "ThreeArgInstruction.h"

ThreeArgInstruction::ThreeArgInstruction(TokenList& tokenList)
	: rd(tokenList[1]), rs(tokenList[2]), rt(tokenList[3]) {
	if (!rd.signatureIs("Rb"))
		throw std::string("\"") + std::string(tokenList[1]) + std::string("\" have to be a register");
	//if (!rs.signatureIs("Rb"))
		//throw std::string("\"") + std::string(tokenList[2]) + std::string("\" have to be a register");

	function = nullptr;
	if (strcmp(tokenList[0], "add") == 0) this->function = add;
	if (strcmp(tokenList[0], "sub") == 0) this->function = sub;
	if (strcmp(tokenList[0], "mul") == 0) this->function = mul;
	if (strcmp(tokenList[0], "addu") == 0) this->function = addu;
	if (strcmp(tokenList[0], "subu") == 0) this->function = subu;
	if (strcmp(tokenList[0], "slt") == 0) this->function = slt;
	if (strcmp(tokenList[0], "or") == 0) this->function = Or;
	if (strcmp(tokenList[0], "and") == 0) this->function = And;

	if (strcmp(tokenList[0], "add.s") == 0) this->function = adds;
	if (strcmp(tokenList[0], "sub.s") == 0) this->function = subs;
	if (strcmp(tokenList[0], "mul.s") == 0) this->function = muls;
	if (strcmp(tokenList[0], "div.s") == 0) this->function = divs;
	if (strcmp(tokenList[0], "xor") == 0) this->function = Xor;

	if (function)
		if (!rt.signatureIs("Rb"))
			throw std::string("\"") + std::string(tokenList[3]) + std::string("\" have to be a register");
		else
			return;

	if (strcmp(tokenList[0], "addi") == 0)this->function = add;
	if (strcmp(tokenList[0], "addiu") == 0) this->function = addu;
	if (strcmp(tokenList[0], "subiu") == 0) this->function = sub;
	if (strcmp(tokenList[0], "andi") == 0) this->function = And;
	if (strcmp(tokenList[0], "ori") == 0) this->function = Or;
	if (strcmp(tokenList[0], "subi") == 0) this->function = sub;
	if (strcmp(tokenList[0], "slti") == 0) this->function = slt;
	if (strcmp(tokenList[0], "sll") == 0) this->function = sll;
	if (strcmp(tokenList[0], "srl") == 0) this->function = srl;
	if (strcmp(tokenList[0], "ori") == 0) this->function = ori;
	if (strcmp(tokenList[0], "sra") == 0) this->function = sra;
	if (function)
		if (!rt.signatureIs("Ii"))
			throw std::string("\"") + std::string(tokenList[3]) + std::string("\" have to be an integer");
		else
			return;

	if (strcmp(tokenList[0], "bge") == 0) this->function = bge;
	if (strcmp(tokenList[0], "beq") == 0) this->function = beq;
	if (strcmp(tokenList[0], "bne") == 0) this->function = bne;
	if (strcmp(tokenList[0], "bge") == 0) this->function = bge;
	if (strcmp(tokenList[0], "blt") == 0) this->function = blt;
	if (strcmp(tokenList[0], "bgt") == 0) this->function = bgt;
	if (strcmp(tokenList[0], "ble") == 0) this->function = ble;

	if (function)
		if (!rt.signatureIs("Ii") && !rt.signatureIs("Li"))
			throw std::string("\"") + std::string(tokenList[3]) + std::string("\" have to be an instruction label or an integer");
		else
			return;
	if (!function)
		throw std::string("cannot resolve \"") + std::string(tokenList[0]) + std::string("\"");
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

void ThreeArgInstruction::bge(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	InstructionOperand pc("$pc");
	if (*(rd.memoryPtr) >= *(rs.memoryPtr))
		*(pc.memoryPtr) = *(rt.memoryPtr);
}

void ThreeArgInstruction::bgt(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	InstructionOperand pc("$pc");
	if (*(rd.memoryPtr) > *(rs.memoryPtr))
		*(pc.memoryPtr) = *(rt.memoryPtr);
}

void ThreeArgInstruction::ble(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	InstructionOperand pc("$pc");
	if (*(rd.memoryPtr) <= *(rs.memoryPtr))
		*(pc.memoryPtr) = *(rt.memoryPtr);
}
void ThreeArgInstruction::blt(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	InstructionOperand pc("$pc");
	if (*(rd.memoryPtr) < *(rs.memoryPtr))
		*(pc.memoryPtr) = *(rt.memoryPtr);
}

void ThreeArgInstruction::adds(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	*((float*)(rd.memoryPtr)) = *((float*)(rd.memoryPtr)) + *((float*)(rd.memoryPtr));
}

void ThreeArgInstruction::subs(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	*((float*)(rd.memoryPtr)) = *((float*)(rd.memoryPtr)) - *((float*)(rd.memoryPtr));
}

void ThreeArgInstruction::muls(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	*((float*)(rd.memoryPtr)) = *((float*)(rd.memoryPtr)) * *((float*)(rd.memoryPtr));
}

void ThreeArgInstruction::divs(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	*((float*)(rd.memoryPtr)) = *((float*)(rd.memoryPtr)) / *((float*)(rd.memoryPtr));
}

void ThreeArgInstruction::ori(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	*rd.memoryPtr = *rs.memoryPtr | *rt.memoryPtr;
}

void ThreeArgInstruction::sra(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	*rd.memoryPtr = *rs.memoryPtr >> *rt.memoryPtr;
}

void ThreeArgInstruction::Xor(InstructionOperand& rd, InstructionOperand& rs, InstructionOperand& rt) {
	*rd.memoryPtr = *rs.memoryPtr ^ *rt.memoryPtr;
}
