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

void Train::InsertFirst(Wagon& wagon)
{
	if (wagon.GetPayload() == "")
	{
		printf("%s. nullptr error", __FUNCTION__);
		return;
	}
	wagons.push_front(wagon);
}

void Train::InsertLast(Wagon& wagon)
{
	wagons.push_back(wagon);
}

#pragma endregion Train

#pragma region LinkedListTester


void LinkedListTester::Test()
{
	train.InsertLast(Wagon("sand"));
	train.InsertLast(Wagon("oil"));
	train.InsertLast(Wagon("gas"));
	train.InsertLast(Wagon("bricks"));
	train.InsertFirst(Wagon("coal"));

	for (auto wagon : train.wagons)
	{
		printf("payload = %s\n", wagon.GetPayload().c_str());
	}
}


#pragma endregion LinkedListTester
