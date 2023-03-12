#include <iostream>
#include <memory>

class Animal {
public:
	using Ptr = std::shared_ptr<Animal>;
	virtual void speak() = 0;
};

class Cat : public Animal {
	void speak() {
		std::cout << "Pisica\n";
	}
};

class Dog : public Animal {
	void speak() {
		std::cout << "Caine\n";
	}
};

class Bird : public Animal {
	void speak() {
		std::cout << "Pasare\n";
	}
};

class Elephant : public Animal {
	void speak() {
		std::cout << "Elefant\n";
	}
};

class Bear : public Animal {
	void speak() {
		std::cout << "Urs\n";
	}
};