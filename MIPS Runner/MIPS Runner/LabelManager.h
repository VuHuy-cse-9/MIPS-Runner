#pragma once

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstring>

#include "SmartPointer.h"
#include "MemoryManager.h"

class LabelManager {
private:
	class LinkedListNode {
	public:
		char* name;
		void* memory;
		bool isInstruction;
		bool haveToDeleteMemory;

		LinkedListNode* next;
	};

	LinkedListNode* root;

	LabelManager();
	LabelManager(const LabelManager&) = delete;

	static SmartPointer<LabelManager> instance;
	bool latestLabelType;

	friend class UIManager;
public:
	~LabelManager();
	static LabelManager* getInstance();

	void* addInstructionLabel(const char*);
	void* addVariableLabel(const char*);
	void* getMemory(const char*);
	bool lastestLabelIsInstruction();
};

