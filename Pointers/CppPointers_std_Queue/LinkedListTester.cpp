#include "LinkedListTester.h"

#pragma region Train

Train::Train()
{
	//printf("%s\n", __FUNCTION__);
}

Train::~Train()
{
	/*
	for (;;)
	{
		Wagon::Ptr wagon = RemoveFirst();
		if (wagon == nullptr)
		{
			break;
		}
		delete wagon;
	}
	*/
	//printf("%s\n", __FUNCTION__);
}

Wagon::Ptr Train::RemoveFirst()
{
	if (wagons.empty()) {
		//ERROR
		return nullptr;
	}
	Wagon::Ptr wagon = wagons.front();
	wagons.pop();
	return wagon;
}

void Train::InsertLast(Wagon::Ptr wagon)
{
	wagons.push(wagon);
}

Wagon::Ptr Train::GetFirst()
{
	if (wagons.empty()) {
		return nullptr;
	}
	return wagons.front();
}

Wagon::Ptr Train::GetLast() {
	if (wagons.empty()) {
		return nullptr;
	}
	return wagons.back();
}
#pragma endregion Train

#pragma region LinkedListTester


void LinkedListTester::Test()
{
	train.InsertLast(std::make_shared<Wagon>("sand"));
	train.InsertLast(std::make_shared<Wagon>("oil"));
	train.InsertLast(std::make_shared<Wagon>("gas"));
	train.InsertLast(std::make_shared<Wagon>("bricks"));
	train.InsertLast(std::make_shared<Wagon>("coal"));

	while (!train.wagons.empty())
	{
		Wagon::Ptr wagon = train.wagons.front();
		printf("payload = %s\n", wagon->GetPayload().c_str());
		train.RemoveFirst();
	}
}


#pragma endregion LinkedListTester
