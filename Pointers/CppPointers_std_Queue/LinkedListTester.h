#pragma once

#include <string>
#include <memory>
#include <queue>

class Wagon
{
	const std::string Payload;

public:
	using Ptr = std::shared_ptr<Wagon>;

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
private:
	Wagon::Ptr GetLast();

public:
	std::queue<Wagon::Ptr> wagons;
	Train();
	~Train();

	Wagon::Ptr GetFirst();
	void InsertLast(Wagon::Ptr wagon);
	Wagon::Ptr RemoveFirst();
};


class LinkedListTester
{
	Train train;

public:
	void Test();
};

