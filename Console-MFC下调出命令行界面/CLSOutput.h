#pragma once
#include <windows.h>
#include <iostream>

class CLSOutput
{
public:
	template <typename T>
	friend CLSOutput& operator<<(CLSOutput& out, T a){
		std::cout << a <<'\t';
		return out;
	}

	CLSOutput() {
		AllocConsole();
		freopen("CONOUT$","w",stdout);
	}

	~CLSOutput() {
		FreeConsole();
	}
};

