#pragma once

#include <string>
#include <map>

class IOperation
{
public:
	virtual int Execute(int n1, int n2) = 0;
};



class ClassTester
{
	std::map<std::string, IOperation*> Operations;

	int Execute(const std::string& op, int n1, int n2);

public:
	ClassTester();
	~ClassTester();

	void Test();
};

