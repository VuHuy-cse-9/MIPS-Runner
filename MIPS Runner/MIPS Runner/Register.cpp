#include "Register.h"

Register::Register()
	:value(0) {
}

Register::Register(int _value)
	: value(_value) {
}

Register::operator int&() {
	return value;
}