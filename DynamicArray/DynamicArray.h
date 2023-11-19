#include <iostream>
#include <cstring>

template <typename T>
class DynamicArray {
private:
    T* array;
    size_t currentSize;
    size_t maxSize;

public:
    DynamicArray();

    ~DynamicArray();

    void addElement(const T& data);

    T& operator[](size_t index);

    T getElement(size_t index);

    void setElement(size_t index, const T& data);

    void clear();

    void print();

    void BubbleSort(int(*comparator)(T a, T b));

};


