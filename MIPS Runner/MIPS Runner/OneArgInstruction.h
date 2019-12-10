#pragma once

#include "Instruction.h"
#include "TokenList.h"
#include "InstructionOperand.h"

// One argument instruction is jump type instruction.

class OneArgInstruction : public Instruction {
private:
	InstructionOperand address;
	void (*function)(InstructionOperand&);

	static void j(InstructionOperand&);
	static void jal(InstructionOperand&);
	static void bc1f(InstructionOperand&);
	static void bc1t(InstructionOperand&);
public:

	OneArgInstruction(TokenList&);

	void execute() override;
};