#include "TwoArgInstruction.h"

TwoArgInstruction::TwoArgInstruction(TokenList& tokenList) :
	rs( tokenList[1]),rt(tokenList[2]) {
	if (!rs.signatureIs("Rb"))
		throw std::string("\"") + std::string(tokenList[1]) + std::string("\" have to be a register");

	function = nullptr;
	if (strcmp(tokenList[0], "abs.s") == 0) this->function = abss;
	if (strcmp(tokenList[0], "abs") == 0) this->function = abss;
	if (strcmp(tokenList[0], "neg.s") == 0) this->function = negs;
	if (strcmp(tokenList[0], "c.eq.s") == 0) this->function = ceqs;
	if (strcmp(tokenList[0], "c.le.s") == 0) this->function = cles;
	if (strcmp(tokenList[0], "c.lt.s") == 0) this->function = clts;
	if (strcmp(tokenList[0], "mfc1") == 0) this->function = mfc1;
	if (strcmp(tokenList[0], "mtc1") == 0) this->function = mtc1;
	if (strcmp(tokenList[0], "cvt.w.s") == 0) this->function = cvtws;
	if (strcmp(tokenList[0], "mult") == 0) this->function = mult;
	if (strcmp(tokenList[0], "div") == 0) this->function = div;
	if (strcmp(tokenList[0], "not") == 0) this->function = Not;
	if (function)
		if (!rt.signatureIs("Rb"))
			throw std::string("\"") + std::string(tokenList[2]) + std::string("\" have to be a register");
		else
			return;

	if (strcmp(tokenList[0], "lui") == 0) this->function = lui;
	if (strcmp(tokenList[0], "li") == 0) this->function = move;
	if (function)
		if (!rt.signatureIs("Ii"))
			throw std::string("\"") + std::string(tokenList[2]) + std::string("\" have to be an integer");
		else
			return;
	
	if (strcmp(tokenList[0], "la") == 0) this->function = la;
	if (function)
		if (!rt.signatureIs("Lv"))
			throw std::string("\"") + std::string(tokenList[2]) + std::string("\" have to be a variable label");
		else
			return;

	if (strcmp(tokenList[0], "sw") == 0) this->function = sw;
	if (strcmp(tokenList[0], "lw") == 0) this->function = lw;
	if (strcmp(tokenList[0], "lwc1") == 0) this->function = lwc1;
	if (strcmp(tokenList[0], "swc1") == 0) this->function = swc1;
	if (function)
		if (!rt.signatureIs("Rw") && !rt.signatureIs("Lv"))
			throw std::string("\"") + std::string(tokenList[2]) + std::string("\" have to be an eclosed register \"offset(register name)\"");
		else
			return;

	if (strcmp(tokenList[0], "move") == 0) this->function = move;
	if (strcmp(tokenList[0], "mov.s") == 0) this->function = movs;
	if (function)
		if (!rt.signatureIs("Rb") && !rt.signatureIs("Lv"))
			throw std::string("\"") + std::string(tokenList[2]) + std::string("\" have to be a register or a variable label");
		else
			return;

	if (strcmp(tokenList[0], "bgez") == 0) this->function = bgez;
	if (strcmp(tokenList[0], "beqz") == 0) this->function = beqz;
	if (function)
		if (!rt.signatureIs("Li") && !rt.signatureIs("Ii"))
			throw std::string("\"") + std::string(tokenList[2]) + std::string("\" have to be a label instruction or immediate interger");

	//if (strcmp(tokenList[0], "cvt.s.w") == 0) this->function = cvtsw;
	if (!function)
		throw std::string("cannot resolve \"") + std::string(tokenList[0]) + std::string("\"");
}

void TwoArgInstruction::execute() {
	if (function)
		function(this->rs, this->rt);
}


void TwoArgInstruction::mult(InstructionOperand& rs, InstructionOperand& rt) {
	InstructionOperand hi("$hi");
	InstructionOperand lo("$lo");
	long long result = (long long) *(rs.memoryPtr) * (long long) * (rt.memoryPtr);
	long long* ptr = &result;
	*(hi.memoryPtr) = ((int*)ptr)[1];
	*(lo.memoryPtr) = ((int*)ptr)[0];
}

void TwoArgInstruction::div(InstructionOperand& rs, InstructionOperand& rt) {
	InstructionOperand hi("$hi");
	InstructionOperand lo("$lo");
	*(hi.memoryPtr) = *(rs.memoryPtr) % *(rt.memoryPtr);
	*(lo.memoryPtr) = *(rs.memoryPtr) / *(rt.memoryPtr);
}

void TwoArgInstruction::lui(InstructionOperand& rs, InstructionOperand& rt) {
	*(rs.memoryPtr) = *(rt.memoryPtr) << 16;
}

void TwoArgInstruction::move(InstructionOperand& rs, InstructionOperand& rt) {
	*(rs.memoryPtr) = *(rt.memoryPtr);
}

void TwoArgInstruction::sw(InstructionOperand& rs, InstructionOperand& rt) {
	if (rt.signatureIs("Rw"))
		*(int*)((char*)(*rt.memoryPtr) + rt.offset) = *rs.memoryPtr;
	if (rt.signatureIs("Lv"))
		*rt.memoryPtr = *rs.memoryPtr;
}

void TwoArgInstruction::lw(InstructionOperand& rs, InstructionOperand& rt) {
	if (rt.signatureIs("Rw"))
		*(rs.memoryPtr) = *(int*)((char*)(*rt.memoryPtr) + rt.offset);
	if (rt.signatureIs("Lv"))
		*rs.memoryPtr = *rt.memoryPtr;
}

void TwoArgInstruction::la(InstructionOperand& rs, InstructionOperand& rt) {
	*(rs.memoryPtr) = (int) rt.memoryPtr;
}

void TwoArgInstruction::abss(InstructionOperand& rs, InstructionOperand& rt) {
	*((float*)rs.memoryPtr) = fabs(*((float*)rt.memoryPtr));
}

void TwoArgInstruction::negs(InstructionOperand& rs, InstructionOperand& rt) {
	*((float*)rs.memoryPtr) = -1 * *((float*)rt.memoryPtr);
}

void TwoArgInstruction::ceqs(InstructionOperand& rs, InstructionOperand& rt) {
	InstructionOperand $32("$32");
	*((float*)rs.memoryPtr) == *((float*)rt.memoryPtr) ? *((float*)$32.memoryPtr) = 1 : *((float*)$32.memoryPtr) = 0;
}

void TwoArgInstruction::cles(InstructionOperand& rs, InstructionOperand& rt) {
	InstructionOperand $32("$32");
	*((float*)rs.memoryPtr) <= *((float*)rt.memoryPtr) ? *((float*)$32.memoryPtr) = 1 : *((float*)$32.memoryPtr) = 0;
}

void TwoArgInstruction::clts(InstructionOperand& rs, InstructionOperand& rt) {
	InstructionOperand $32("$32");
	*((float*)rs.memoryPtr) < *((float*)rt.memoryPtr) ? *((float*)$32.memoryPtr) = 1 : *((float*)$32.memoryPtr) = 0;
}

void TwoArgInstruction::lwc1(InstructionOperand& rs, InstructionOperand& rt) {
	if (rt.signatureIs("Rb")) 
		*((int*)rs.memoryPtr) = *(int*)((char*)(*rt.memoryPtr) + rt.offset);
	else
		*(int*)(rs.memoryPtr) = *(int*)(rt.memoryPtr);
}

void TwoArgInstruction::swc1(InstructionOperand& rs, InstructionOperand& rt) {
	if (rt.signatureIs("Rw"))
		*(int*)((char*)(*rt.memoryPtr) + rt.offset) = *((int*)rs.memoryPtr);
	else
		*(int*)(rt.memoryPtr) = *(int*)(rs.memoryPtr);
}

void TwoArgInstruction::movs(InstructionOperand& rs, InstructionOperand& rt) {
	*((float*)rs.memoryPtr) = *((float*)rt.memoryPtr);
}

//rs is a int register -> need compile here
void TwoArgInstruction::mfc1(InstructionOperand& rs, InstructionOperand& rt) {
	*((float*)rs.memoryPtr) = *((float*)rt.memoryPtr);
}
//rs is a int register -> need compile here
void TwoArgInstruction::mtc1(InstructionOperand& rs, InstructionOperand& rt) {
	*((float*)rt.memoryPtr) = *((float*)rs.memoryPtr);
}

void TwoArgInstruction::cvtws(InstructionOperand& rs, InstructionOperand& rt) {
	*((float*)rs.memoryPtr) = *(rt.memoryPtr);
}

//void TwoArgInstruction::cvtsw(InstructionOperand& rs, InstructionOperand& rt) {
//	*((float*)rt.memoryPtr) = *(rs.memoryPtr);
//}

void TwoArgInstruction::bgez(InstructionOperand& rs, InstructionOperand& rt) {
	InstructionOperand pc("$pc");
	if (*rs.memoryPtr >= 0)  *pc.memoryPtr = *rt.memoryPtr;
}

void TwoArgInstruction::Not(InstructionOperand& rs, InstructionOperand& rt) {
	*rs.memoryPtr = ~*rt.memoryPtr;
}

void TwoArgInstruction::beqz(InstructionOperand& rs, InstructionOperand& rt) {
	InstructionOperand pc("$pc");
	if (*rs.memoryPtr == 0)  *pc.memoryPtr = *rt.memoryPtr;
}






