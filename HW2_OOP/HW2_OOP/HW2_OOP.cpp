#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;


class Animal
{
public:
    virtual void makeSound() const = 0; // Pure virtual function
    virtual ~Animal() {} // Virtual destructor
};


class Dog : public Animal
{
public:
    void makeSound() const override
    {
        cout << "Woof!\n";
    }
};

class Cat : public Animal
{
public:
    void makeSound() const override
    {
        cout << "Meow!\n";
    }
};

class Cow : public Animal
{
public:
    void makeSound() const override
    {
        cout << "Moo!\n";
    }
};


// 랜덤 동물을 생성하는 함수
Animal* createRandomAnimal() {
    int randomNum = std::rand() % 3; // 0, 1, 2 중 하나
    switch (randomNum) {
    case 0: return new Dog();
    case 1: return new Cat();
    case 2: return new Cow();
    default: return nullptr;
    }
}




class Zoo {
private:
    Animal* animals[10]; // 동물 객체를 저장하는 포인터 배열
    int count = 0;       // 현재 저장된 동물의 수
public:
    void addAnimal(Animal* animal) {
        if (count < 10) {
            animals[count++] = animal;
        }
    }

    void performActions() {
        for (int i = 0; i < count; ++i) {
            animals[i]->makeSound();
        }
    }

    ~Zoo() {
        for (int i = 0; i < count; ++i) {
            delete animals[i];
        }
    }
};





int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // 시드 설정

    int AnimalNumber = 0;
    const int animalCount = 10; // 원하는 동물 
    cin >> AnimalNumber;

    Animal* animals[animalCount];

    for (int i = 0; i < AnimalNumber; ++i) {
        animals[i] = createRandomAnimal();
    }
    for (int i = 0; i < AnimalNumber; ++i) {
        animals[i]->makeSound();
        delete animals[i];
    }




    return 0;
}
