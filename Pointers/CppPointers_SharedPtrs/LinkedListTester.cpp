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
	wagon->Next = First;
	First = wagon;
}

Wagon::Ptr Train::RemoveFirst()
{
	Wagon::Ptr wagon = First;
	if (wagon != nullptr)
	{
		First = wagon->Next;
		wagon->Next = nullptr;
	}
	return wagon;
}

void Train::InsertLast(Wagon::Ptr wagon)
{
	if (First == nullptr) {
		InsertFirst(wagon);
		return;
	}
	Wagon::Ptr lastWagon = GetLast();
	lastWagon->Next = wagon;
		
}

void Train::InsertAfter(Wagon::Ptr position, Wagon::Ptr wagon) {
	wagon->Next = position->Next;
	position->Next = wagon;
}

Wagon::Ptr Train::RemoveAfter(Wagon::Ptr position) {
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
	Wagon::Ptr saved = position->Next;
	position->Next = saved->Next;
	saved->Next = nullptr;
	return saved;
}

Wagon::Ptr Train::RemoveLast()
{
	if (First == nullptr) {
		return nullptr;
	}
	if (First->Next == nullptr) {
		return RemoveFirst();
	}
	Wagon::Ptr wagon = First;
	while (wagon->Next->Next != nullptr) {
		wagon = wagon->Next;
	}
	return RemoveAfter(wagon);
}


Wagon::Ptr Train::GetFirst()
{
	return First;
}

Wagon::Ptr Train::GetLast() {
	if (First == nullptr) {
		return nullptr;
	}
	Wagon::Ptr wagon = First;
	while (wagon->Next != nullptr) {
		wagon = wagon->Next;
	}
	return wagon;
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

	for (Wagon::Ptr wagon = train.GetFirst(); wagon != nullptr; wagon = wagon->Next)
	{
		printf("payload=%s\n", wagon->GetPayload().c_str());
	}
}


#pragma endregion LinkedListTester
