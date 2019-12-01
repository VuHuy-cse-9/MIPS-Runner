#include "TextProcessor.h"
#include "ThreeArgInstruction.h"

int main() {
	TextProcessor textProcessor;
	textProcessor.readSourceFile();
	textProcessor.parseSourceToInstruction();

	/* for testing
	TokenList tokenlist;
	tokenlist.pushBack((char*)"sub");
	tokenlist.pushBack((char*)"$s0");
	tokenlist.pushBack((char*)"$zero");
	tokenlist.pushBack((char*)"2");
	ThreeArgInstruction ins(tokenlist);
	ins.execute();
	*/
	return 0;
}