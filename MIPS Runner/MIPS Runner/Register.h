#pragma once
class Register
{
private:
	int value;
public:
	Register();
	Register(int);

	operator int&();
};

