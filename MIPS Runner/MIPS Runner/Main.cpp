#include <iostream>
#include <string>
#include "UIManager.h";

int main() {
	try {
		UIManager::run();
	}
	catch (std::string message) {
		UIManager::printErrorMessage(message.c_str());
	}
}