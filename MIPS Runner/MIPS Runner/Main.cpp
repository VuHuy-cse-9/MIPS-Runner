#include "TextProcessor.h"

int main() {
	TextProcessor textProcessor;
	textProcessor.readSourceFile();
	textProcessor.parseSourceToInstruction();
}