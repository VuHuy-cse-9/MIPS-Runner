#pragma once

#include <iostream>
#include <cstring>
#include <stdint.h>
#include "InstructionOperand.h"

#include "SmartPointer.h"

class MemoryManager {
private:
	static const int VARIABLE_MEMORY_SIZE;
	static const int STACK_MEMORY_SIZE;

	char* variableMemory;
	int variableMemoryPointer;

	char* stackMemory;
	int stackMemoryPointer;

	int* registerMemory;
	float* floating_pointRegisterMemory;

	static SmartPointer<MemoryManager> instance;

	MemoryManager();
	MemoryManager(const MemoryManager&) = delete;
	MemoryManager& operator=(const MemoryManager&) = delete;

	friend class UIManager;
public:
	static const int REGISTER_MEMORY_SIZE;
	static const int FLOATINGPOINTREGISTER_MEMORY_SIZE;
	static const char* REGISTER_NAME[];
	static const char* REGISTER_BASIC_NAME[];
	static const char* FLOATING_POINT_BASIC_NAME[];

	~MemoryManager();
	static MemoryManager* getInstance();

	void* getVariableMemoryPointer();
	template<typename Type>
	Type* allocateVariableMemory(int _size, Type _value) {
		Type* returnPointer = (Type*)(this->variableMemory + this->variableMemoryPointer);
		this->variableMemoryPointer += _size;
		memcpy(returnPointer, &_value, sizeof(Type));
		return returnPointer;
	}
	int* getRegister(const char*);
	float* getFloatingPointRegister(const char*);
	void log();
	void storeString(char*);
};