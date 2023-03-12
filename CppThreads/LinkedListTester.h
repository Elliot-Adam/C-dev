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
	//Wagon()
	//{
	//}
	~Wagon()
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
	Wagon* First = nullptr;

public:
	Train();
	~Train();

	void InsertFirst(Wagon* wagon);
	Wagon* RemoveFirst();
	void InsertLast(Wagon* wagon);
	Wagon* RemoveLast();
	Wagon* GetFirst();
};


class LinkedListTester
{
	Train Train;

public:
	void Test();
};

