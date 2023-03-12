#pragma once

#include <string>

class Wagon
{
	const std::string Payload;

public:
	Wagon* Next = nullptr;

public:
	Wagon(const std::string& payload)
		: Payload(payload)
	{
		printf("%s\n", __FUNCTION__);
	}

	const std::string& GetPayload() const
	{
		return Payload;
	}
};

class Train
{
	Wagon* first;

public:
	Train();
	~Train();
	void InsertLast(Wagon* wagon);
	Wagon* GetFirst();
};


class LinkedListTester
{
	const int total = 4;
	Train train = Train();

public:
	void Test();
};

