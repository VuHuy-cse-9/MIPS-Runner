#pragma once

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstring>

// for .data directive with mutiple value, use name less allocator
// ex:
// x: .word 2, 3
// .word 4, 5
// x only store adress of first word (the word that hold value of 2).
// those next adress simply sit next to x. so we got an array.

class LabelManager {
private:
	static int RESERVED_OFFSET;

	static char** labelNameList;
	static char** labelMemoryList;
	static int labelListSize;
	static int labelListReservedSize;

public:
	static void reserveLabel(int);
	static void* addLabel(const char*, int, int);
	static void* getLabel(const char*);
};

