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
std::map<int, Wagon::Ptr> Incrementer(std::map<int, Wagon::Ptr> Map, bool positive) {
	std::map<int, Wagon::Ptr> newMap;
	if (positive){
		for (std::map<int, Wagon::Ptr>::iterator it = Map.begin(); it != Map.end(); ++it) {
			newMap.insert(std::pair<int, Wagon::Ptr>(it->first + 1, it->second));
		}
	}
	else {
		for (std::map<int, Wagon::Ptr>::iterator it = Map.begin(); it != Map.end(); ++it) {
			newMap.insert(std::pair<int, Wagon::Ptr>(it->first - 1, it->second));
		}
	}
	return newMap;
}




void Train::Insert(int wagonNumber, Wagon::Ptr wagon)
{
	if (wagon == nullptr)
	{
		printf("%s. nullptr error", __FUNCTION__);
		return;
	}
	//int num = wagons.size();
	wagons.insert(std::pair<int, Wagon::Ptr>(wagonNumber, wagon));
}



Wagon::Ptr Train::GetFirst()
{
	if (wagons.empty()) {
		return nullptr;
	}
	return wagons[1];
}

Wagon::Ptr Train::GetLast() {
	if (wagons.empty()) {
		return nullptr;
	}
	return wagons[wagons.size() - 1];
}
#pragma endregion Train

#pragma region LinkedListTester

void LinkedListTester::Test()
{
	train.Insert(2,std::make_shared<Wagon>("sand"));
	train.Insert(3,std::make_shared<Wagon>("oil"));
	train.Insert(4,std::make_shared<Wagon>("gas"));
	train.Insert(5,std::make_shared<Wagon>("bricks"));
	train.Insert(1,std::make_shared<Wagon>("coal"));

	for (auto const& it : train.wagons)
	{
		printf("payload=%s\n", it.second->GetPayload().c_str());
	}
}


#pragma endregion LinkedListTester
