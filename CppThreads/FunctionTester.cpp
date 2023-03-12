#include "FunctionTester.h"

#include <map>

int FunctionTester::Add(int n1, int n2)
{
	return n1 + n2;
}

int FunctionTester::Sub(int n1, int n2)
{
	return n1 - n2;
}

int FunctionTester::Mul(int n1, int n2)
{
	return n1 * n2;
}

int FunctionTester::Div(int n1, int n2)
{
	// TOO: ensure n2 != 0
	return n1 / n2;
}

int FunctionTester::Execute(const std::string& op, int n1, int n2)
{
	static const std::map<std::string, Operation> operations =
	{
		{ "ADD", Add },
		{ "SUB", Sub },
		{ "MUL", Mul },
		{ "DIV", Div }
	};
	auto it = operations.find(op);
	if (it != operations.end())
	{
		return it->second(n1, n1);
	}
	printf("unknown op=%s", op.c_str());
	return 0;
}


void FunctionTester::Test()
{
	int six = Execute("MUL", 2, 3);
	
}
