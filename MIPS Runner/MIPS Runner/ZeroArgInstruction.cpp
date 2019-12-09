#include "ZeroArgInstruction.h"

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

	// print and read from console different than the debug one.
	switch (*v0.memoryPtr) {
	case 1:
		// PRINT_INT
		std::cout << *a0.memoryPtr;
		break;
	case 4:
		// PRINT_STRING

		std::cout << (char*)a0.memoryPtr;
		break;
	case 5:
		// READ_INT
		std::cin >> *v0.memoryPtr;
		break;
	//case 8: {
	//	//READ_STRING
	//	std::cout << "access";
	//	char c = 0;
	//	int length = 0;
	//	char* str = new char[1000];
	//	while ( c != '\n') {
	//		std::cin >> c;
	//		str[length] = c;
	//		++length;
	//	}
	//	char* buffer = new char[length];
	//	for (int i = 0; i < length - 1; ++i) {
	//		buffer[i] = str[i];
	//	}
	//	buffer[length - 1] = '\0';
	//	delete[] str;
	//	//TODO:
	//	MemoryManager::getInstance()->storeStringToMemory(buffer);
	//	delete[] buffer;
	//}
	//	break;
	case 10:
		// EXIT
		throw 0;
	case 11:
		// PRINT_CHAR
		std::cout << *(char*)(a0.memoryPtr);
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