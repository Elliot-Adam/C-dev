#pragma once

#include <string>
#include <memory>
#include <set>

class Wagon
{
	const std::string Payload;
	const int number = 0;

public:
	using Ptr = std::shared_ptr<Wagon>;

public:
	Wagon(const std::string& payload,int wagonNumber)
		: Payload(payload), number(wagonNumber)
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
	int GetWagonNumber() const
	{
		return number;
	}

};


class Train
{
	void Insert(Wagon::Ptr wagon);
public:

	struct comparePayload {
		bool operator() (const Wagon::Ptr& lhs, const Wagon::Ptr& rhs) const {
			return lhs->GetPayload() < rhs->GetPayload();
		}
	};
	struct compareWagonNumber {
		bool operator() (const Wagon::Ptr& lhs, const Wagon::Ptr& rhs) const {
			return lhs->GetWagonNumber() < rhs->GetWagonNumber();
		}
	};	
	//std::set<Wagon::Ptr, comparePayload> wagons;
	//std::set<Wagon::Ptr, compareWagonNumber> wagons;
	std::set<int> wagons;

	Train();
	~Train();

	Wagon::Ptr GetFirst();
	Wagon::Ptr Remove(Wagon::Ptr wagon);

	void operator+=(const Wagon::Ptr& wagon) {
		Insert(wagon);
	}
};


class LinkedListTester
{
	Train train;

public:
	void Test();
};

