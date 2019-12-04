#pragma once

#include <cstring>
#include <iostream>
#include <vector>

#include "Instruction.h"
#include "TokenList.h"
#include "InstructionOperand.h"

class ThreeArgInstruction : public Instruction {
protected:
	InstructionOperand rd, rs, rt;
	void (*function)(InstructionOperand&, InstructionOperand&, InstructionOperand&);

	static void add(InstructionOperand&, InstructionOperand&, InstructionOperand&);
	static void addu(InstructionOperand&, InstructionOperand&, InstructionOperand&);
	static void sub(InstructionOperand&, InstructionOperand&, InstructionOperand&);
	static void subu(InstructionOperand&, InstructionOperand&, InstructionOperand&);
	static void And(InstructionOperand&, InstructionOperand&, InstructionOperand&); // and is now allow
	static void Or(InstructionOperand&, InstructionOperand&, InstructionOperand&);
	static void sll(InstructionOperand&, InstructionOperand&, InstructionOperand&);
	static void srl(InstructionOperand&, InstructionOperand&, InstructionOperand&);
	static void mul(InstructionOperand&, InstructionOperand&, InstructionOperand&);
	static void slt(InstructionOperand&, InstructionOperand&, InstructionOperand&);
	static void beq(InstructionOperand&, InstructionOperand&, InstructionOperand&);
	static void bne(InstructionOperand&, InstructionOperand&, InstructionOperand&);
	
public:
	ThreeArgInstruction(TokenList&);

	void execute() override;
};