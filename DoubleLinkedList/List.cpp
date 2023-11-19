#include "List.h"

template<typename T>
void List<T>::outOfRangeMessage(int index)
{
    cerr << "Error: Index " << index << " is out of range.\n";
}

template<typename T>
List<T>::List()
{
    size = 0;
    head = nullptr;
    tail = nullptr;
}

template<typename T>
List<T>::~List()
{
    clear();
}


template<typename T>
void List<T>::push_front(T data)
{
    Node<T>* newNode = new Node<T>(data);
    if (head == nullptr || compare(data, head->data) < 0) {
        // If the list is empty or the new element is smaller than the current head,
        // insert it as the new head.
        newNode->pNext = head;
        if (head != nullptr) {
            head->pPrev = newNode;
        }
        head = newNode;
    }
    else {
        // Otherwise, find the appropriate position to insert the new element.
        Node<T>* current = head;
        while (current->pNext != nullptr && compare(data, current->pNext->data) >= 0) {
            current = current->pNext;
        }
        newNode->pNext = current->pNext;
        newNode->pPrev = current;
        if (current->pNext != nullptr) {
            current->pNext->pPrev = newNode;
        }
        current->pNext = newNode;
    }
    size++;
}

template<typename T>
void List<T>::push_back(T data)
{
    Node<T>* newNode = new Node<T>(data);
    if (tail == nullptr || compare(data, tail->data) >= 0) {
        // If the list is empty or the new element is greater than the current tail,
        // insert it as the new tail.
        newNode->pPrev = tail;
        if (tail != nullptr) {
            tail->pNext = newNode;
        }
        tail = newNode;
    }
    else {
        // Otherwise, find the appropriate position to insert the new element.
        Node<T>* current = tail;
        while (current->pPrev != nullptr && compare(data, current->pPrev->data) < 0) {
            current = current->pPrev;
        }
        newNode->pNext = current;
        newNode->pPrev = current->pPrev;
        if (current->pPrev != nullptr) {
            current->pPrev->pNext = newNode;
        }
        current->pPrev = newNode;
    }
    size++;
}



template<typename T>
void List<T>::pop_front()
{
    if (head == nullptr) return; // No elements to pop

    Node<T>* temp = head;//The head pointer points to the node to be removed.
    //To ensure that we don't lose the connection to this node, a temporary pointer temp 
    //is used to hold a reference to the current head node
    if (head == tail)
    {
        // Only one element in the list, set head and tail to nullptr
        head = tail = nullptr;
    }
    else
    {
        head = head->pNext;
        head->pPrev = nullptr;
    }
    delete temp;
    size--;
}

template<typename T>
void List<T>::pop_back()
{
    if (tail == nullptr) return;
    Node<T>* temp = tail;
    if (head == tail)
    {
        head = tail = nullptr;
    }
    else
    {
        tail = tail->pPrev;
        tail->pNext = nullptr;
    }
    delete temp;
    size--;
}

template<typename T>
void List<T>::clear()
{
    while (size)
    {
        pop_front();

        if (size)
        {
            pop_back();
        }
    }
    cout << "The list is clean";
}

template<typename T>
void List<T>::print()
{
    for (int i = 0; i < GetSize(); i++)
    {
        cout << (*this)[i] << " ";
    }
    cout << endl;
}


template<typename T>
Node<T>* List<T>::startIndexSearch(int index)
{
    if (index < 0 || index >= size)
    {
        outOfRangeMessage(index);
    }
    else if (index > size / 2)
    {
        int counter = size - 1;
        Node<T>* current = tail;
        while (counter != index)
        {
            current = current->pPrev;
            counter--;
        }
        return current;
    }
    else
    {
        int counter = 0;
        Node<T>* current = head;
        while (counter != index)
        {
            current = current->pNext;
            counter++;
        }
        return current;
    }
}

template<typename T>
T& List<T>::operator[](const int index)
{
    Node<T>* current = startIndexSearch(index);
    return current->data;
}


template<typename T>
void List<T>::replaceAt(T data, int index)
{
    (*this)[index] = data;
}

template<typename T>
void List<T>::addAt(T data, int index)
{
    if (index == 0)
    {
        push_front(data);
    }
    else if (index == size - 1)
    {
        push_back(data);
    }
    else if (index > 0 && index < size - 1)
    {
        Node<T>* previous = startIndexSearch(index);
        Node<T>* newNode = new Node<T>(data, previous->pNext, previous);
        previous->pNext = newNode;
        newNode->pNext->pPrev = newNode;
        size++;
    }
    else
    {
        outOfRangeMessage(index);
    }
}

template<typename T>
void List<T>::deleteAt(int index)
{
    if (index == 0)
    {
        pop_front();
    }
    else if (index == size - 1)
    {
        pop_back();
    }
    else if (index > 0 && index < size - 1)
    {
        Node<T>* current = startIndexSearch(index);
        current->pPrev->pNext = current->pNext;
        current->pNext->pPrev = current->pPrev;
        delete current;
        size--;
    }
    else
    {
        outOfRangeMessage(index);
    }
}


template<typename T>
Node<T>* List<T>::searchByData(T data)
{
    Node<T>* currentHead = this->head;
    Node<T>* currentTail = this->tail;

    while (currentHead != nullptr || currentTail != nullptr)
    {
        if (currentHead->data == data)
        {
            return currentHead;
        }
        if (currentTail->data == data)
        {
            return currentTail;
        }

        // Move the pointers in both directions
        currentHead = currentHead->pNext;
        currentTail = currentTail->pPrev;

    }

    return nullptr;
}

template<typename T>
bool List<T>::deleteByData(T data)
{
    Node<T>* nodeToDelete = searchByData(data);

    if (nodeToDelete != nullptr)
    {
        if (nodeToDelete == head)
        {
            pop_front();
        }
        else if (nodeToDelete == tail)
        {
            pop_back();
        }
        else
        {
            nodeToDelete->pPrev->pNext = nodeToDelete->pNext;
            nodeToDelete->pNext->pPrev = nodeToDelete->pPrev;
            delete nodeToDelete;
            size--;
        }
        return true;
    }

    return false;

}


template<typename T>
int compare(const T& a, const T& b) {
    if (a == b) {
        return 0;
    }
    else if (a < b) {
        return -1;
    }
    else {
        return 1;
    }
}
