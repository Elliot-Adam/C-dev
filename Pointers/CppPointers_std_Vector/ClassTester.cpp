#include "ClassTester.h"

#include <map>
#include <memory>	// shared_ptr



class Add : public IOperation
{
public:
	Add()
	{
		printf("%s\n", __FUNCTION__);
	}
	~Add()
	{
		printf("%s\n", __FUNCTION__);
	}

	int Execute(int n1, int n2) final
	{
		return n1 + n2;
	}
};

class Sub : public IOperation
{
public:
	Sub()
	{
		printf("%s\n", __FUNCTION__);
	}
	~Sub()
	{
		printf("%s\n", __FUNCTION__);
	}

	int Execute(int n1, int n2) final
	{
		return n1 - n2;
	}
};

class Mul : public IOperation
{
public:
	Mul()
	{
		printf("%s\n", __FUNCTION__);
	}
	~Mul()
	{
		printf("%s\n", __FUNCTION__);
	}
	int Execute(int n1, int n2) final
	{
		return n1 * n2;
	}
};

class Div : public IOperation
{
public:
	Div()
	{
		printf("%s\n", __FUNCTION__);
	}
	~Div()
	{
		printf("%s\n", __FUNCTION__);
	}
	int Execute(int n1, int n2) final
	{
		// TOO: ensure n2 != 0
		return n1 / n2;
	}
};



ClassTester::ClassTester()
{
	Operations["ADD"] = new Add;
	Operations["SUB"] = new Sub;
	Operations["MUL"] = new Mul;
	Operations["DIV"] = new Div;
}

ClassTester::~ClassTester()
{
	for (auto it : Operations)
	{
		delete it.second;
	}
}


int ClassTester::Execute(const std::string& op, int n1, int n2)
{
	auto it = Operations.find(op);
	if (it != Operations.end())
	{
		return it->second->Execute(n1, n1);
	}
	printf("unknown op=%s", op.c_str());
	return 0;
}


void ClassTester::Test()
{
	int six = Execute("MUL", 2, 3);

}

