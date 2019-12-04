#pragma once

#include <cstring>
#include "SmartPointer.h"

class MemoryManager {
private:
	static const int MEMORY_SIZE;

	char* variableMemory;
	int variableMemoryPointer;

	static SmartPointer<MemoryManager> instance;

	MemoryManager();
	MemoryManager(const MemoryManager&) = delete;
public:
	~MemoryManager();
	static MemoryManager* getInstance();

	void* getMemoryPointer();

	template<typename Type>
	Type* allocateVariableMemory(int, Type);
};

