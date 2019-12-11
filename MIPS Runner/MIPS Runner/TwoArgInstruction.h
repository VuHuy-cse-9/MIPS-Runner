#pragma once

#include "Instruction.h"
#include "TokenList.h"
#include "InstructionOperand.h"
#include <cmath>

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
	static void la(InstructionOperand&, InstructionOperand&);
	static void bgez(InstructionOperand&, InstructionOperand&);
	static void beqz(InstructionOperand&, InstructionOperand&);
	static void Not(InstructionOperand&, InstructionOperand&);

	static void abss(InstructionOperand&, InstructionOperand&);
	static void negs(InstructionOperand&, InstructionOperand&);
	static void ceqs(InstructionOperand&, InstructionOperand&);
	static void cles(InstructionOperand&, InstructionOperand&);
	static void clts(InstructionOperand&, InstructionOperand&);

	static void lwc1(InstructionOperand&, InstructionOperand&);
	static void swc1(InstructionOperand&, InstructionOperand&);

	static void movs(InstructionOperand&, InstructionOperand&);
	static void mfc1(InstructionOperand&, InstructionOperand&);
	static void mtc1(InstructionOperand&, InstructionOperand&);

	static void cvtws(InstructionOperand&, InstructionOperand&);
	//static void cvtsw(InstructionOperand&, InstructionOperand&);


	
public:

	TwoArgInstruction(TokenList&);
	void execute() override;
};