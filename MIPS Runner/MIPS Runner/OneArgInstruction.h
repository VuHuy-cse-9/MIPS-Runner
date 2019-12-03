#pragma once

#include "Instruction.h"
#include "Register.h"
#include "TokenList.h"

// Not tested yet.
// One argument instruction is jump type instruction.

class OneArgInstruction : public Instruction {
private:
	Register address;
	void (*function)(Register&);

	static void j(Register&);
	static void jal(Register&);
public:

	OneArgInstruction(TokenList&);

	void execute() override;
};