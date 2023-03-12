#include "LinkedListTester.h"

#pragma region Train

Train::Train()
{
	//printf("%s\n", __FUNCTION__);
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
	//printf("%s\n", __FUNCTION__);
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
	if (First == nullptr) {
		InsertFirst(wagon);
		return;
	}
	Wagon* lastWagon = GetLast();
	lastWagon->Next = wagon;
		
}

void Train::InsertAfter(Wagon* position, Wagon* wagon) {
	wagon->Next = position->Next;
	position->Next = wagon;
}

Wagon* Train::RemoveAfter(Wagon* position) {
	//position not nullptr
	if (position == nullptr) {
		//REPORT ERROR 
		//TODO
		return nullptr;
	}
	if (position->Next == nullptr) {
		//is last
		return nullptr;
	}
	Wagon* saved = position->Next;
	position->Next = saved->Next;
	saved->Next = nullptr;
	return saved;
}

Wagon* Train::RemoveLast()
{
	if (First == nullptr) {
		return nullptr;
	}
	if (First->Next == nullptr) {
		return RemoveFirst();
	}
	Wagon* wagon = First;
	while (wagon->Next->Next != nullptr) {
		wagon = wagon->Next;
	}
	return RemoveAfter(wagon);
}


Wagon* Train::GetFirst()
{
	return First;
}

Wagon* Train::GetLast() {
	if (First == nullptr) {
		return nullptr;
	}
	Wagon* wagon = First;
	while (wagon->Next != nullptr) {
		wagon = wagon->Next;
	}
	return wagon;
}
#pragma endregion Train



#pragma region LinkedListTester


void LinkedListTester::Test()
{
	train.InsertLast(new Wagon("sand"));
	train.InsertLast(new Wagon("oil"));
	train.InsertLast(new Wagon("gas"));
	train.InsertLast(new Wagon("bricks"));
	train.InsertFirst(new Wagon("coal"));

	for (Wagon* wagon = train.GetFirst(); wagon != nullptr; wagon = wagon->Next)
	{
		printf("payload=%s\n", wagon->GetPayload().c_str());
	}
}


#pragma endregion LinkedListTester
