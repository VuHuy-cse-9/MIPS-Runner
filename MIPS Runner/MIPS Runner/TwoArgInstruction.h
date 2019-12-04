#pragma once

#include "Instruction.h"
#include "Register.h"
#include "TokenList.h"


// PROBLEM: sw require address of rt.
class TwoArgInstruction : public Instruction {
protected:
	Register rs, rt;
	void (*function)(Register&, Register&);

	static void mult(Register&, Register&);
	static void move(Register&, Register&);
	static void lui(Register&, Register&);
	static void div(Register&, Register&);
	static void lw(Register&, Register&);
public:

	TwoArgInstruction(TokenList&);
	void execute() override;
};