#include "LinkedListTester.h"
#include <iostream>

#pragma region Train

Train::Train()
{
	Wagon* carriage[size];
	printf("%s\n", __FUNCTION__);
}

Train::~Train() {
}

void Train::InsertLast(Wagon* wagon) {

}

Wagon* Train::GetFirst() {
	return first;
}


#pragma endregion Train



#pragma region LinkedListTester


void LinkedListTester::Test()
{
	train.InsertLast(Wagon("sand"));
	train.InsertLast(Wagon("oil"));
	train.InsertLast(Wagon("gas"));
	train.InsertLast(Wagon("bricks"));

	for (Wagon* wagon = train.GetFirst(); wagon != nullptr; wagon = wagon->Next)
	{
		printf("payload=%s\n", wagon->GetPayload().c_str());
	}
}


#pragma endregion LinkedListTester
