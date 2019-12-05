#pragma once
#include  <iostream>
#include "LabelManager.h"

class DataAnalyse
{
private:
	char** tokenData;
	int tokenListSize;
	char** parseDataToToken(const char* line);
public:
	DataAnalyse(const char* line);
};

