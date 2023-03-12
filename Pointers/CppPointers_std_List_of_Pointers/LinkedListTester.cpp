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

void Train::InsertFirst(Wagon::Ptr wagon)
{
	if (wagon == nullptr)
	{
		printf("%s. nullptr error", __FUNCTION__);
		return;
	}
	wagons.push_front(wagon);
}

Wagon::Ptr Train::RemoveFirst()
{
	if (wagons.empty()) {
		//ERROR
		return nullptr;
	}
	Wagon::Ptr wagon = wagons.front();
	wagons.pop_front();
	return wagon;
}

void Train::InsertLast(Wagon::Ptr wagon)
{
	wagons.push_back(wagon);
}

Wagon::Ptr Train::RemoveLast()
{
	if (wagons.empty()) {
		return nullptr;
	}
	Wagon::Ptr lastWagon = wagons.back();
	wagons.pop_back();
	return lastWagon;
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
	train.InsertFirst(std::make_shared<Wagon>("coal"));

	for (auto wagon : train.wagons)
	{
		printf("payload=%s\n", wagon->GetPayload().c_str());
	}
}


#pragma endregion LinkedListTester
