#pragma once

#include <string>
#include <memory>
#include <vector>

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
	std::vector<Wagon::Ptr> wagons;
	Train();
	~Train();

	Wagon::Ptr GetFirst();
	void Insert(Wagon::Ptr wagon);
	Wagon::Ptr Remove();
};


class LinkedListTester
{
	Train train;

public:
	void Test();
};

