#pragma once

#include <string>

class FunctionTester
{
	using Operation = int(*)(int, int);
	//typedef int Operation(int n1, int n2);	// define the type of a function which takes 2 ints, and returns int.

	//  the following finctions are all of the same "Operation" type
	static int Add(int n1, int n2);
	static int Sub(int n1, int n2);
	static int Mul(int n1, int n2);
	static int Div(int n1, int n2);

	int Execute(const std::string& op, int n1, int n2);

public:
	void Test();
};

