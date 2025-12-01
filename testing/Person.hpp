#include <iostream>
using namespace std;

class Person {
    string name;
    int age;

public:
    Person(string name, int age) {
        this->name = name;
        this->age = age;
    }

    string getName() {
        return this->name;
    }
};
