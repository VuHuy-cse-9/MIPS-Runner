#pragma once

#include "Instruction.h"
#include "Register.h"
#include "TokenList.h"

// Zero argument instruction is infact label declaration.
class ZeroArgInstruction : public Instruction {
private:
	Register address;

public:
	ZeroArgInstruction(TokenList&);

	void execute() override;
};

