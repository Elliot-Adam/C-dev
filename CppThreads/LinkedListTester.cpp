#include "LinkedListTester.h"

#pragma region Train

Train::Train()
{
	printf("%s\n", __FUNCTION__);
}

Train::~Train()
{
	for (;;)
	{
		Wagon* wagon = RemoveFirst();
		if (wagon == nullptr)
		{
			break;
		}
		delete wagon;
	}
	printf("%s\n", __FUNCTION__);
}

void Train::InsertFirst(Wagon* wagon)
{
	if (wagon == nullptr)
	{
		printf("%s. nullptr error", __FUNCTION__);
		return;
	}
	wagon->Next = First;
	First = wagon;
}

Wagon* Train::RemoveFirst()
{
	Wagon* wagon = First;
	if (wagon != nullptr)
	{
		First = wagon->Next;
		wagon->Next = nullptr;
	}
	return wagon;
}

void Train::InsertLast(Wagon* wagon)
{
	//TODO:
}

Wagon* Train::RemoveLast()
{
	//TODO:
	return nullptr;
}


Wagon* Train::GetFirst()
{
	return First;
}


#pragma endregion Train



#pragma region LinkedListTester


void LinkedListTester::Test()
{
	Train.InsertFirst(new Wagon("sand"));
	Train.InsertFirst(new Wagon("oil"));
	Train.InsertFirst(new Wagon("gas"));
	Train.InsertFirst(new Wagon("bricks"));

	for (Wagon* wagon = Train.GetFirst(); wagon != nullptr; wagon = wagon->Next)
	{
		printf("payload=%s\n", wagon->GetPayload().c_str());
	}
}


#pragma endregion LinkedListTester
