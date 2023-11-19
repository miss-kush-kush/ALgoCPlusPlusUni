#ifndef LIST_H
#define LIST_H
#include "Node.h"
#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

template<typename T>
class List
{
public:
    List();
    ~List();
    void push_back(T data); // a
    void push_front(T data); // b
    void pop_back(); // c
    void pop_front(); // d
    void clear(); // j
    void print(); // k
    Node<T>* startIndexSearch(int index);
    T& operator[](const int index); // e // 
    void replaceAt(T data, int index); // f
    int GetSize() { return size; }
    void addAt(T data, int index); // i
    void deleteAt(int index); // h
    Node<T>* searchByData(T data); // g
    bool deleteByData(T data); // h


private:
    int size;
    Node<T>* head;
    Node<T>* tail;
    void outOfRangeMessage(int);
};

template<typename T>
int compare(const T&, const T&);


#endif
