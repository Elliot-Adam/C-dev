#include <iostream>
#include <list>
#include <memory>
#include "classes.cpp"





class Zoo {
public:
	std::list<Animal::Ptr> animals;
	void capture(Animal::Ptr animal) {
		if (animal == nullptr) {
			throw std::exception("Tried catching a null ptr");
		}
		animals.push_back(animal);
	}

	Animal::Ptr releaseLast() {
		if (animals.empty()) {
			throw std::exception("Releasing nothing");
		}
		Animal::Ptr animal = animals.back();
		animals.pop_back();
		return animal;
	}
};

void Test() {
	Zoo zoo;

	zoo.capture(std::make_shared<Dog>());
	zoo.capture(std::make_shared<Cat>());
	zoo.capture(std::make_shared<Bird>());
	zoo.capture(std::make_shared<Elephant>());
	zoo.capture(std::make_shared<Bear>());

	Animal::Ptr released = zoo.releaseLast();

	for (auto animal : zoo.animals) {
		animal->speak();
	}

	printf("released ");
	released->speak();
}
int main() {
	Test();
	return 0;
}