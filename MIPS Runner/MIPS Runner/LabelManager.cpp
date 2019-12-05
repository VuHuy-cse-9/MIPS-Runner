#include "LabelManager.h"

SmartPointer<LabelManager> LabelManager::instance = nullptr;

LabelManager::LabelManager() {
	this->root = nullptr;
}

LabelManager::~LabelManager() {
	while (this->root) {
		LinkedListNode* next = this->root->next;

		delete[] this->root->name;
		if (this->root->haveToDeleteMemory)
			delete this->root->memory;
		delete this->root;

		this->root = next;
	}
}

LabelManager* LabelManager::getInstance() {
	if (!instance)
		instance = new LabelManager;
	return instance;
}

void* LabelManager::addVariableLabel(const char* _name) {
	LinkedListNode* newNode = new LinkedListNode;
	newNode->name = new char[strlen(_name) + 1];
	strcpy(newNode->name, _name);

	newNode->haveToDeleteMemory = false;
	newNode->memory = MemoryManager::getInstance()->getVariableMemoryPointer();
	newNode->next = this->root;
	this->root = newNode;

	return newNode->memory;
}

void* LabelManager::addInstructionLabel(const char* _name) {
	LinkedListNode* newNode = new LinkedListNode;
	newNode->name = new char[strlen(_name) + 1];
	strcpy(newNode->name, _name);

	newNode->haveToDeleteMemory = true;
	newNode->memory = new int;
	newNode->next = this->root;
	this->root = newNode;

	return newNode->memory;
}

void* LabelManager::getMemory(const char* _name) {
	LinkedListNode* seeker = this->root;
	while (seeker) {
		if (strcmp(seeker->name, _name) == 0)
			return seeker->memory;
		seeker = seeker->next;
	}

	return nullptr;
}