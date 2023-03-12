#include <iostream>

class Animal {
public:
    virtual void speak() = 0;
};

class Dog : public Animal {
    void speak() {
        std::cout << "Caine\n";
    }
};

class Cat : public Animal {
    void speak() {
        std::cout << "Pisica\n";
    }
};

class Elephant : public Animal {
    void speak() {
        std::cout << "Elefant\n";
    }
};

class Shark : public Animal {
    void speak() {
        std::cout << "Rechin\n";
    }
};

class Parrot : public Animal {
    void speak() {
        std::cout << "Papagal\n";
    }
};