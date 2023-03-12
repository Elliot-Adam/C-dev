#pragma once

#include <string>
#include <memory>

class Wagon
{
	const std::string Payload;

public:
	using Ptr = std::shared_ptr<Wagon>;
	Wagon::Ptr Next = nullptr;

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
	
	Wagon::Ptr First = nullptr;

private:
	Wagon::Ptr GetLast();
	void InsertAfter(Wagon::Ptr position, Wagon::Ptr wagon);
	Wagon::Ptr RemoveAfter(Wagon::Ptr position);
public:
	Train();
	~Train();

	Wagon::Ptr GetFirst();
	void InsertFirst(Wagon::Ptr wagon);
	Wagon::Ptr RemoveFirst();
	void InsertLast(Wagon::Ptr wagon);
	Wagon::Ptr RemoveLast();
};


class LinkedListTester
{
	Train train;

public:
	void Test();
};

