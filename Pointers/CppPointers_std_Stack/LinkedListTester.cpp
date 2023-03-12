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

void Train::Insert(Wagon::Ptr wagon)
{
	if (wagon == nullptr)
	{
		printf("%s. nullptr error", __FUNCTION__);
		return;
	}
	wagons.push(wagon);
}

Wagon::Ptr Train::Remove()
{
	if (wagons.empty()) {
		//ERROR
		return nullptr;
	}
	Wagon::Ptr wagon = wagons.top();
	wagons.pop();
	return wagon;
}

Wagon::Ptr Train::GetLast() {
	if (wagons.empty()) {
		return nullptr;
	}
	return wagons.top();
}
#pragma endregion Train

#pragma region LinkedListTester


void LinkedListTester::Test()
{
	train.Insert(std::make_shared<Wagon>("sand"));
	train.Insert(std::make_shared<Wagon>("oil"));
	train.Insert(std::make_shared<Wagon>("gas"));
	train.Insert(std::make_shared<Wagon>("bricks"));
	train.Insert(std::make_shared<Wagon>("coal"));

	while (!train.wagons.empty())
	{
		Wagon::Ptr wagon = train.Remove();
		printf("payload = %s\n", wagon->GetPayload().c_str());
	}
}


#pragma endregion LinkedListTester
