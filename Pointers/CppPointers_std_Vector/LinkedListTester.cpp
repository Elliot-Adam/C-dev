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
	wagons.push_back(wagon);
}

Wagon::Ptr Train::Remove()
{
	if (wagons.empty()) {
		throw std::exception("Removes from empty train");
	}
	Wagon::Ptr wagon = wagons.front();
	wagons.pop_back();
	return wagon;
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
	train.Insert(std::make_shared<Wagon>("sand"));
	train.Insert(std::make_shared<Wagon>("oil"));
	train.Insert(std::make_shared<Wagon>("gas"));
	train.Insert(std::make_shared<Wagon>("bricks"));
	train.Insert(std::make_shared<Wagon>("coal"));

	for (auto wagon : train.wagons)
	{
		printf("payload=%s\n", wagon->GetPayload().c_str());
	}
	for (int i = 0; i < train.wagons.size(); i++) {
		const Wagon::Ptr& wagon = train.wagons[i];
		printf("payload=%s\n", wagon->GetPayload().c_str());
	}
}


#pragma endregion LinkedListTester
