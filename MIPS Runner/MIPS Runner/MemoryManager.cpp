#include "MemoryManager.h"

const int MemoryManager::VARIABLE_MEMORY_SIZE = 1 << 20;

const int MemoryManager::STACK_MEMORY_SIZE = 1 << 10;

const int MemoryManager::REGISTER_MEMORY_SIZE = 35;
const char* MemoryManager::REGISTER_NAME[] = { "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra", "$hi", "$lo", "$pc" };
const char* MemoryManager::REGISTER_BASIC_NAME[] = { "$0", "$1", "$2", "$3", "$4", "$5", "$6", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$16", "$17", "$18", "$19", "$20", "$21", "$22", "$23", "$24", "$25", "$26", "$27", "$28", "$29", "$30", "$31", "$32", "$33", "$34" };

SmartPointer<MemoryManager> MemoryManager::instance = nullptr;

MemoryManager::MemoryManager() {
	this->variableMemory = new char[VARIABLE_MEMORY_SIZE];
	this->variableMemoryPointer = 0;

	this->stackMemory = new char[STACK_MEMORY_SIZE];
	this->stackMemoryPointer = STACK_MEMORY_SIZE - 1;

	this->registerMemory = new int[REGISTER_MEMORY_SIZE];
}

MemoryManager::~MemoryManager() {
	delete[] this->variableMemory;
	delete[] this->stackMemory;
	delete[] this->registerMemory;
}

MemoryManager* MemoryManager::getInstance() {
	if (!instance) 
		instance = new MemoryManager;
	return instance;
}

template<typename Type>
Type* MemoryManager::allocateVariableMemory(int _size, Type _value) {
	Type* returnPointer = (Type*) this->variableMemory[this->variableMemoryPointer];
	this->variableMemoryPointer += _size;

	memcpy(returnPointer, &_value, sizeof(Type));
	return returnPointer;
}

void* MemoryManager::getMemoryPointer() {
	return this->variableMemory + this->variableMemoryPointer;
}

int* MemoryManager::getRegister(const char* _name) {
	for (int i = 0; i < REGISTER_MEMORY_SIZE; ++i)
		if (strcmp(_name, REGISTER_NAME[i]) == 0 || strcmp(_name, REGISTER_BASIC_NAME[i]) == 0)
			return this->registerMemory + i;
}