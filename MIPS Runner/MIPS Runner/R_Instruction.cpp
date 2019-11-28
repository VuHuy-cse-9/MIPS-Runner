#include "R_Instruction.h"

R_Instruction::R_Instruction(const char* text) {
}

void R_Instruction::execute() {
	function(this->rd, this->rs, this->rt);
}