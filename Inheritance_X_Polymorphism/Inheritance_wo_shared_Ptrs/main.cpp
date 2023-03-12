#include <list>
#include "classes.cpp"

class Zoo {
public:
    std::list<Animal*> animals;
    void capture(Animal* animal) {
        if (animal == nullptr) {
            return;
        }
        animals.push_back(animal);
    }

    Animal* release() {
        if (animals.empty()) {
            return nullptr;
        }
        Animal* released = animals.back();
        animals.pop_back();
        return released;
    }
};

void Test() {
    Zoo zoo;

    //Animal defs
    Dog* dog = new Dog();
    Cat* cat = new Cat();
    Elephant* elephant = new Elephant();
    Shark* shark = new Shark();
    Parrot* parrot = new Parrot();

    //Capturing animals
    zoo.capture(dog);
    zoo.capture(cat);
    zoo.capture(elephant);
    zoo.capture(shark);
    zoo.capture(parrot);

    //Releases last one
    Animal* released = zoo.release();

    //All the animals speak
    for (auto animal : zoo.animals) {
        animal->speak();
    }

    //Prints out name of released animal
    std::cout << "Released ";
    released->speak();

    //Deletes pointers
    delete dog;
    delete cat;
    delete elephant;
    delete shark;
    delete released;
}

int main() {
    // Write C++ code here
    Test();
    return 0;
}