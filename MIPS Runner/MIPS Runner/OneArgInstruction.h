#pragma once

#include "Instruction.h"
#include "Register.h"
#include "TokenList.h"

class OneArgInstruction : public Instruction {
private:
	Register rd;
	void (*function)(Register&);

	static void j(Register&);
	static void jal(Register&);
public:

	OneArgInstruction(TokenList&);

	void execute() override;
};