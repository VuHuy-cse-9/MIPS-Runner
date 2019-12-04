#pragma once

template<typename Type>
class SmartPointer {
private:
	Type* pointer;

public:
	SmartPointer();
	SmartPointer(Type*);
	~SmartPointer();

	operator Type* () &;
};


template<typename Type>
SmartPointer<Type>::SmartPointer() {
	pointer = nullptr;
}

template<typename Type>
SmartPointer<Type>::SmartPointer(Type* _source) {
	pointer = _source;
}

template<typename Type>
SmartPointer<Type>::~SmartPointer() {
	delete pointer;
}

template<typename Type>
SmartPointer<Type>::operator Type* ()& {
	return pointer;
}
