#include "ThreeArgInstruction.h"

const char* ThreeArgInstruction::THREE_ARG_INSTRUCTION_LIST[] = { "add", "sub", "and", "or" };
const int ThreeArgInstruction::THREE_ARG_INSTRUCTION_LIST_SIZE = 4;

ThreeArgInstruction::ThreeArgInstruction(const TokenList& listOfToken) {

};

void ThreeArgInstruction::execute() {
	function(this->rd, this->rs, this->rt);
}