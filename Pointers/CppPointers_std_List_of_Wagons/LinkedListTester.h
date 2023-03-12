#pragma once

#include <string>
#include <memory>
#include <list>

class Wagon
{
	const std::string Payload;

public:
	Wagon(const std::string& payload)
		: Payload(payload)
	{
		//printf("%s\n", __FUNCTION__);
	}
	//Wagon()
	//{
	//}
	~Wagon()
	{
		//printf("%s\n", __FUNCTION__);
	}

	const std::string& GetPayload() const
	{
		return Payload;
	}
};

class Train
{
public:
	std::list<Wagon> wagons;
	Train();
	~Train();

	void InsertFirst(Wagon& wagon);
	void InsertLast(Wagon& wagon);
};


class LinkedListTester
{
	Train train;

public:
	void Test();
};

