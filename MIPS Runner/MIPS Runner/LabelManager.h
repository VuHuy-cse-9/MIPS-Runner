#pragma once

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstring>

#include "SmartPointer.h"

class LabelManager {
private:
	class LinkedListNode {
	public:
		char* name;
		void* memory;
		bool haveToDeleteMemory;

		LinkedListNode* next;
	};

	LinkedListNode* root;

	LabelManager();
	LabelManager(const LabelManager&) = delete;

	static SmartPointer<LabelManager> instance;
public:
	~LabelManager();
	static LabelManager* getInstance();

	void* addInstructionLabel(const char*);
	// TODO: add addVariableLabel method.
	void* getMemory(const char*);
};

