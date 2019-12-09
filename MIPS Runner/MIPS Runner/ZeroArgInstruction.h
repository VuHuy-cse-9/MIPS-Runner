#pragma once

#include "Instruction.h"
#include "InstructionOperand.h"
#include "TokenList.h"
#include "LabelManager.h"
#include "MemoryManager.h"

// Zero argument instruction is infact label declaration or a system call.
class ZeroArgInstruction : public Instruction {
private:
	InstructionOperand address;
	void(*function)(InstructionOperand&);

	static void syscall(InstructionOperand&);
	static void setLabelValue(InstructionOperand&);
public:
	ZeroArgInstruction(TokenList&);

	void execute() override;
};

