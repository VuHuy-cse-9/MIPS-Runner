#pragma once

#include <cstring>
#include <iostream>
#include <vector>

#include "Instruction.h"
#include "TokenList.h"
#include "Register.h"

class ThreeArgInstruction : public Instruction {
protected:
	Register rd, rs, rt;
	void (*function)(Register&, Register&, Register&);

	static void add(Register&, Register&, Register&);
	static void addu(Register&, Register&, Register&);
	static void sub(Register&, Register&, Register&);
	static void subu(Register&, Register&, Register&);
	static void And(Register&, Register&, Register&); // and is now allow
	static void Or(Register&, Register&, Register&);
	static void sll(Register&, Register&, Register&);
	static void srl(Register&, Register&, Register&);
	static void mul(Register&, Register&, Register&);
	static void slt(Register&, Register&, Register&);
	static void beq(Register&, Register&, Register&);
	static void bne(Register&, Register&, Register&);
	
public:
	ThreeArgInstruction(TokenList&);

	void execute() override;
};