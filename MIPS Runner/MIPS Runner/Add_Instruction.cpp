#include "Add_Instruction.h"

void Add_Instruction::execute() {
	rd = rs + rt;
}