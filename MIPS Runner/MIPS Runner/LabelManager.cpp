#include "LabelManager.h"

int LabelManager::RESERVED_OFFSET = 10;

char** LabelManager::labelNameList = nullptr;
char** LabelManager::labelMemoryList = nullptr;
int LabelManager::labelListSize = 0;
int LabelManager::labelListReservedSize = 0;

// delete dynamically allocated size.
void LabelManager::reserveLabel(int size) {
	if (labelListReservedSize >= size)
		return;

	char** newLabelNameList = new char* [size];
	char** newLabelMemoryList = new char* [size];
	for (int i = 0; i < labelListSize; ++i) {
		newLabelNameList[i] = labelNameList[i];
		newLabelMemoryList[i] = labelMemoryList[i];
	}

	delete[] labelNameList;
	labelNameList = newLabelNameList;
	delete[] labelMemoryList;
	labelMemoryList = newLabelMemoryList;

	labelListReservedSize = size;
}

void* LabelManager::addLabel(const char* name, int size, int value) {
	if (labelListSize >= labelListReservedSize)
		reserveLabel(labelListSize + RESERVED_OFFSET);

	if (name) {
		labelNameList[labelListSize] = new char[strlen(name) + 1];
		strcpy(labelNameList[labelListSize], name);
	}
	else
		labelNameList[labelListSize] = nullptr;

	labelMemoryList[labelListSize] = new char[size];
	memcpy(labelMemoryList + labelListSize, &value, sizeof(int));

	return labelNameList[labelListSize++];
}

void* LabelManager::getLabel(const char* name) {
	for (int i = 0; i < labelListSize; ++i)
		if (labelNameList[i])
			if (strcmp(name, labelNameList[i]) == 0) 
				return labelMemoryList + i;

	return nullptr;
}