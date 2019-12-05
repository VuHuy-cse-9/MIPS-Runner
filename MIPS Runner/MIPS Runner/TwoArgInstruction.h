#pragma once

#include "Instruction.h"
#include "TokenList.h"
#include "InstructionOperand.h"


// PROBLEM: sw require address of rt.
class TwoArgInstruction : public Instruction {
protected:
	InstructionOperand rs, rt;
	void (*function)(InstructionOperand&, InstructionOperand&);

	static void mult(InstructionOperand&, InstructionOperand&);
	static void move(InstructionOperand&, InstructionOperand&);
	static void lui(InstructionOperand&, InstructionOperand&);
	static void div(InstructionOperand&, InstructionOperand&);
	static void sw(InstructionOperand&, InstructionOperand&);
	static void lw(InstructionOperand&, InstructionOperand&);
public:

	TwoArgInstruction(TokenList&);
	void execute() override;
};