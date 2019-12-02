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
	
public:
	
	static const char* THREE_ARG_INSTRUCTION_LIST[];
	static const int THREE_ARG_INSTRUCTION_LIST_SIZE;

	ThreeArgInstruction(TokenList&);

	void execute() override;
};