#include "ZeroArgInstruction.h"


void ZeroArgInstruction::storeToStringMemory() {
	InstructionOperand a1("$a1");
	char* buffer = new char[*a1.memoryPtr + 1];
	std::cin >> buffer;
	buffer[*a1.memoryPtr] = '\0';
	MemoryManager::getInstance()->storeString(buffer);
}

ZeroArgInstruction::ZeroArgInstruction(TokenList& tokenList)  
	: address(nullptr, 0){
	if (strcmp(tokenList[0], "syscall") == 0)
		this->function = syscall;
	else {
		this->address.memoryPtr = (int*)LabelManager::getInstance()->addInstructionLabel(tokenList[0]);
		this->function = setLabelValue;
	}
}

void ZeroArgInstruction::execute() {
	this->function(address);
}

void ZeroArgInstruction::setLabelValue(InstructionOperand& address) {
	InstructionOperand pc("$pc");
	*(address.memoryPtr) = *(pc.memoryPtr);
}

void ZeroArgInstruction::syscall(InstructionOperand& address) {
	InstructionOperand v0("$v0");
	InstructionOperand a0("$a0");
	InstructionOperand a1("$a1");
	InstructionOperand f0("$f0");
	InstructionOperand f12("$f12");

	// print and read from console different than the debug one.
	switch (*v0.memoryPtr) {
	case 1:
		// PRINT_INT
		std::cout << *a0.memoryPtr << '\n';
		break;
	case 2:
		//PRINT_FLOAT
		std::cout << *((float*)f12.memoryPtr) << '\n';
		break;
	case 4:
		// PRINT_STRING
		std::cout << (char*)(*a0.memoryPtr) << '\n';
		break;
	case 5:
		// READ_INT
		std::cin >> *v0.memoryPtr;
		break;
	case 6:
		//READ_FLOAT
		std::cin >> *((float*)f0.memoryPtr);
		break;
	case 8: 
		//READ_STRING
		storeToStringMemory();
		break;
	case 10:
		// EXIT
		throw 0;
	case 11:
		// PRINT_CHAR
		std::cout << *(char*)(a0.memoryPtr) << '\n';
		break;
	case 12:
		// READ_CHAR
		std::cin >> *(char*)(v0.memoryPtr);
		break;
	case 17:
		// EXIT2
		throw *a0.memoryPtr;
		break;
	}
}