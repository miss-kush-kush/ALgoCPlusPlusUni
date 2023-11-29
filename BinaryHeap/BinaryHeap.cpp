#include<iostream>
#include<climits>
#include <set>
#include "MaxHeap.h"

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

const string maleNames[] = { "John", "Michael", "Robert", "William", "James" };
const string femaleNames[] = { "Mary", "Jennifer", "Linda", "Patricia", "Elizabeth" };
const string genders[] = { "Male", "Female" };

Person generateRandomPerson() {
    std::string name, gender;
    int age;

    if (rand() % 2 == 0) {
        name = maleNames[rand() % 5];
        gender = "Male";
    }
    else {
        name = femaleNames[rand() % 5];
        gender = "Female";
    }

    age = rand() % 100;

    return Person(name, age, gender);
}

template <typename T>
int comparator(T a, T b)
{
    if (a < b)
    {
        return -1;
    }
    else if (a > b)
    {
        return 1;
    }
    else
    {
        return 0;
    }

};

int (*ageComparator)(Person, Person) = [](Person a, Person b)
    {
        return comparator(a.age, b.age);
    };


int main() {

    //const int MAX_ORDER = 7; // maksymalny rzad wielkosci dodawanych danych
    //MaxHeap <Person>* bh = new MaxHeap <Person>();
    //for (int o = 1; o <= MAX_ORDER; o++)
    //{
    //    const int n = pow(10, o); // rozmiar danych
    //    // dodawanie do kopca
    //    clock_t t1 = clock();
    //    for (int i = 0; i < n; i++) 
    //    {
    //        Person newPerson = generateRandomPerson(); // losowe dane
    //        bh->insert(newPerson, ageComparator); 
    //    }
    //    clock_t t2 = clock();

    //    // wypis na ekran aktualnej postaci kopca ( skrotowej ) oraz pomiarow czasowych
    //    double timeToAdd = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
    //    cout << "Czas dodawania " << n << " elementów: " << timeToAdd << " sekund" << endl;
    //    
    //    // pobieranie ( i usuwanie ) elementu maksymalnego z kopca
    //    t1 = clock();
    //    for (int i = 0; i < n; i++) {
    //        Person pulled = bh->removeMax_Root(ageComparator); // argument : wskaznik na komparator
    //        cout << pulled.age;
    //        // ewentualny wypis na ekran danych elementu pobranego ( przy malym eksperymencie )
    //    }
    //    t2 = clock();
    //    double timeToDelete = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
    //    cout << "Czas usuwania " << n << " elementów: " << timeToDelete << " sekund" << endl;

    //    bh->clear(); 
    //}
    //delete bh;

    const int MAX_ORDER = 7; // maksymalny rzad wielkosci dodawanych danych
    MaxHeap <int>* bh = new MaxHeap <int>();
    for (int o = 1; o <= MAX_ORDER; o++)
    {
        const int n = pow(10, o); // rozmiar danych
        // dodawanie do kopca
        clock_t t1 = clock();
        for (int i = 0; i < n; i++)
        {
            int data = rand()%n; // losowe dane
            bh->insert(data, comparator);
        }
        clock_t t2 = clock();

        // wypis na ekran aktualnej postaci kopca ( skrotowej ) oraz pomiarow czasowych
        double timeToAdd = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
        cout << "Czas dodawania " << n << " elementów: " << timeToAdd << " sekund" << endl;

        // pobieranie ( i usuwanie ) elementu maksymalnego z kopca
        t1 = clock();
        for (int i = 0; i < n; i++) {
            int pulled = bh->removeMax_Root(comparator); // argument : wskaznik na komparator
            //cout << pulled;
            // ewentualny wypis na ekran danych elementu pobranego ( przy malym eksperymencie )
        }
        t2 = clock();
        double timeToDelete = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
        cout << "Czas usuwania " << n << " elementów: " << timeToDelete << " sekund" << endl;

        bh->clear();
    }
    delete bh;

    return 0;
}