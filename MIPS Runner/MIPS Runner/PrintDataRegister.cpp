#include "PrintDataRegister.h"

PrintDataRegister::PrintDataRegister() {
	std::cout << std::left << std::setw(15) << "Basic Name:"
		<< std::left << std::setw(18) << "Name Register:"
		<< "Memory:\n";
	for (int i = 0; i < 35; ++i) {
		std::cout << " " << std::left << std::setw(15) << MemoryManager::REGISTER_BASIC_NAME[i]
			<< std::left << std::setw(18) << MemoryManager::REGISTER_BASIC_NAME[i]
			<< 0 << '\n';
	}
}
