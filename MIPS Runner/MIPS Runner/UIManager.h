#pragma once

#include<iostream>
#include<iomanip>
#include <string>
#include <cstring>

#include "InstructionOperand.h"
#include "MemoryManager.h"
#include "LabelManager.h"
#include "TextProcessor.h"
#include "Processor.h"

class UIManager
{
	static const int WALL_SIZE;
	static const int NUMBER_OF_RUNNING_LINE_SHOW;

	static void printWall(const char*);
	static void clearScreen();
	static void printVariableData();
	static void printRegisterData();
	static void printSoureCode();
	static void printRunningCode();
	static void pauseAndWaitInput(const char*);

public:
	static void run();
	static void printCompileErrorMessage(const char*);
};

