#include "MemoryManager.h"

const int MemoryManager::MEMORY_SIZE = 1 << 20;
SmartPointer<MemoryManager> MemoryManager::instance = nullptr;

MemoryManager::MemoryManager() {
	this->variableMemory = new char[MEMORY_SIZE];
	this->variableMemoryPointer = 0;
}

MemoryManager::~MemoryManager() {
	delete[] this->variableMemory;
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