#pragma once

template<typename Type>
class SmartPointer {
private:
	Type* pointer;

public:
	SmartPointer() {
		this->pointer = nullptr;
	}

	SmartPointer(Type* _source) {
		this->pointer = _source;
	}
	~SmartPointer() {
		delete this->pointer;
	}

	SmartPointer& operator = (Type* _operand)& {
		this->pointer = _operand;
		return *this;
	}

	operator Type* ()& {
		return this->pointer;
	}
};
