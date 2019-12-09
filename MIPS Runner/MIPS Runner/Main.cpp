#include <iostream>
#include <string>
#include "UIManager.h";

int main() {
	try {
		UIManager::run();
	}
	catch (std::string message) {
		UIManager::printCompileErrorMessage(message.c_str());
	}
}