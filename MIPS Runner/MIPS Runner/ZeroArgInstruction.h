#pragma once

#include "Instruction.h"
#include "InstructionOperand.h"
#include "TokenList.h"
#include "LabelManager.h"

// Zero argument instruction is infact label declaration or a system call.
class ZeroArgInstruction : public Instruction {
private:
	InstructionOperand address;

public:
	ZeroArgInstruction(TokenList&);

	void execute() override;
};

