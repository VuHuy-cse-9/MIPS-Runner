#include "MemoryManager.h"
#pragma warning(disable : 4996)

const int MemoryManager::VARIABLE_MEMORY_SIZE = 1 << 20;

const int MemoryManager::STACK_MEMORY_SIZE = 1 << 10 + 1;

const int MemoryManager::REGISTER_MEMORY_SIZE = 35;
const char* MemoryManager::REGISTER_NAME[] = { "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra", "$hi", "$lo", "$pc" };
const char* MemoryManager::REGISTER_BASIC_NAME[] = { "$0", "$1", "$2", "$3", "$4", "$5", "$6", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$16", "$17", "$18", "$19", "$20", "$21", "$22", "$23", "$24", "$25", "$26", "$27", "$28", "$29", "$30", "$31", "$32", "$33", "$34" };
SmartPointer<MemoryManager> MemoryManager::instance = nullptr;
bool MemoryManager::isIgnoreString = false;

MemoryManager::MemoryManager() {
	this->variableMemory = new char[VARIABLE_MEMORY_SIZE];
	this->variableMemoryPointer = 0;

	this->stackMemory = new char[STACK_MEMORY_SIZE];
	this->stackMemoryPointer = STACK_MEMORY_SIZE - 1;

	// $sp actually does not represent stack pointer, the one present stack pointer is stackMemory + stackMemoryPointer
	this->registerMemory = new int[REGISTER_MEMORY_SIZE];
	for (int i = 0; i < REGISTER_MEMORY_SIZE; ++i)
		registerMemory[i] = 0;
}

// A bug appear when trying to stackMemory.
MemoryManager::~MemoryManager() {
	delete[] this->variableMemory;
	// TODO: A bug appear when execute this line of code, fix it.
	delete[] this->stackMemory;
	delete[] this->registerMemory;
}

MemoryManager* MemoryManager::getInstance() {
	if (!instance)
		instance = new MemoryManager;
	return instance;
}

void* MemoryManager::getVariableMemoryPointer() {
	return this->variableMemory + this->variableMemoryPointer;
}


int* MemoryManager::getRegister(const char* _name) {
	if (strcmp(_name, REGISTER_NAME[29]) == 0 || strcmp(_name, REGISTER_BASIC_NAME[29]) == 0)
		return (int*)(this->stackMemory + this->stackMemoryPointer);

	for (int i = 0; i < REGISTER_MEMORY_SIZE; ++i)
		if (strcmp(_name, REGISTER_NAME[i]) == 0 || strcmp(_name, REGISTER_BASIC_NAME[i]) == 0)
			return this->registerMemory + i;

	return nullptr;
}

void MemoryManager::log() {
	for (int i = 0; i < REGISTER_MEMORY_SIZE; ++i)
		if (i != 29)
			std::cout << REGISTER_BASIC_NAME[i] << "\t\t" << REGISTER_NAME[i] << "\t\t" << registerMemory[i] << '\n';
		else 
			std::cout << REGISTER_BASIC_NAME[i] << "\t\t" << REGISTER_NAME[i] << "\t\t" << *(int*)(this->stackMemory + this->stackMemoryPointer) << '\n';
}

//still bug here
void MemoryManager::storeString(char* _buffer) {
	InstructionOperand a0("$a0");
	char* ptr = (char*)*a0.memoryPtr;
	strcpy(ptr, _buffer);
}



