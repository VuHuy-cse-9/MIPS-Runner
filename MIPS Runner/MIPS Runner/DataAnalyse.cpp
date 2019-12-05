#include "DataAnalyse.h"

char** DataAnalyse::parseDataToToken(const char* line) {

}

DataAnalyse::DataAnalyse(const char* line) {
	int count = 2; // e.g . word
	for (int i = 0; i < strlen(line); ++i) {
		if (line[i] == ',') {
			++count;
		}
	}
	tokenData = new char*[count + 1];
	tokenData[count] = 0;
	tokenData = parseDataToToken(line); // parse to Token here? if it is label
	// if it is label ? - > tokenData will have one token -> 
	switch (tokenListSize)
	{
	case 1:
		// it a label
	default:
		//
		break;
	}
	
}