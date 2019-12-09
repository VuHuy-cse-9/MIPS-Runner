#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <fstream>
#include <string>

#include "Instruction.h"
#include "ZeroArgInstruction.h"
#include "OneArgInstruction.h"
#include "TwoArgInstruction.h"
#include "ThreeArgInstruction.h"
#include "TokenList.h"
#include "DataAnalyse.h"
#include "SmartPointer.h"

class TextProcessor
{
private:
	const int MAX_LINE_LENGTH = 255;
	// For storing source code data.
	char* sourceCode;
	int sourceCodeSize;
	int lineCount;
	int textSegmentBeginLine;

	TextProcessor();
	TextProcessor(const TextProcessor&) = delete;

	bool isSpacing(char);
	bool isEmptyLine(const char*);
	char* lineEnd(char*);
	void markComment(char*&);
	bool extractLabel(char*&, char*&);
	bool extractOpCode(char*&, char*&);
	bool extractArgument(char*&, char*&);
	void standarize(char*&);
	void standarize();
	void recognizeDataText(Instruction**&, char*, int&);
	Instruction* parseLineToInstruction(char*);

	static SmartPointer<TextProcessor> instance;

	friend class UIManager;
public:
	~TextProcessor();

	static TextProcessor* getInstance();
	void readSourceFile();
	void parseSourceToInstruction(Instruction**&, int&);
};
