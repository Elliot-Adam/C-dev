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
	wagons.insert(wagon);
}

Wagon::Ptr Train::Remove(Wagon::Ptr wagon)
{
	/*
	if (wagons.empty()) {
		return nullptr;
	}
	*/
	//Wagon::Ptr selectedWagon = *wagons.find(wagon);
	std::set<Wagon::Ptr>::iterator it = wagons.find(wagon);
	if (it == wagons.end()) {
		return nullptr;
	}
	wagons.erase(it);
	return wagon;
}


Wagon::Ptr Train::GetFirst()
{
	if (wagons.empty()) {
		return nullptr;
	}
	return *wagons.begin();

}


#pragma endregion Train

#pragma region LinkedListTester


void LinkedListTester::Test()
{
	train += std::make_shared<Wagon>("sand", 2);
	train += std::make_shared<Wagon>("oil", 3);
	train += std::make_shared<Wagon>("gas", 4);
	train += std::make_shared<Wagon>("bricks", 5);
	train += std::make_shared<Wagon>("coal", 1);

	for (auto wagon : train.wagons)
	{
		printf("payload=%s\n", wagon->GetPayload().c_str());
	}
}


#pragma endregion LinkedListTester
