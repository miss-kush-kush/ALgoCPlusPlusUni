#include <iostream>
#include <cstring>

class Person {
public:
    
    std::string name;
    int age;
    std::string gender;

    Person()
    {
        age = 20;
        name = "Liza";
        gender = "female";

    };
    Person(const std::string& _name, int _age, const std::string& _gender)
        : name(_name), age(_age), gender(_gender) {}

    friend std::ostream& operator<<(std::ostream& os, const Person& person) {
        os << "Name: " << person.name << ", Age: " << person.age << ", Gender: " << person.gender;
        return os;
    }
};
