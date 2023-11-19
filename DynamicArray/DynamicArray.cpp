#include <iostream>
#include <cstring>
#include "DynamicArray.h"
using namespace std;

template<typename T>
DynamicArray<T>::DynamicArray() {
	maxSize = 1;
	currentSize = 0;
	array = new T[maxSize];
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
	delete[] array;
}

template<typename T>
void DynamicArray<T>::addElement(const T& data) {
	if (currentSize == maxSize) {
		// If the array is full, double its size
		maxSize *= 2;
		T* newArray = new T[maxSize];
		for (size_t i = 0; i < currentSize; i++) {
			newArray[i] = array[i];
		}
		delete[] array;
		array = newArray;
	}
	array[currentSize] = data;
	currentSize++;
}

template<typename T>
T& DynamicArray<T>::operator[](size_t index)
{
	if (index < currentSize) {
		return array[index];
	}
	else {
		throw std::out_of_range("Index out of range");
	}
}

template<typename T>
T DynamicArray<T>::getElement(size_t index)
{
	if (index < currentSize) {
		return array[index];
	}
	else {
		throw std::out_of_range("Index out of range");
	}
}

template<typename T>
void DynamicArray<T>::setElement(size_t index, const T& data)
{
	if (index < currentSize) {
		array[index] = data;
	}
	else {
		throw std::out_of_range("Index out of range");
	}
}

template<typename T>
void DynamicArray<T>::clear()
{
	delete[] array;
	maxSize = 1;
	currentSize = 0;
	array = new T[maxSize];
}

template<typename T>
void DynamicArray<T>::print() {
	std::cout << "Current Size: " << currentSize << "\n";
	std::cout << "Max Size: " << maxSize << "\n";

	for (size_t i = 0; i < currentSize; i++) {
		std::cout << i << ": " << *(array[i]) << "\n";
	}
}

template <typename T>
void DynamicArray<T>::BubbleSort(int (*comparator)(T a, T b)) {
	bool swapped;  // Flag to track whether any swaps were made
	for (size_t i = 0; i < currentSize - 1; i++) {
		swapped = false;  // Initialize the flag for this pass
		for (size_t j = 0; j < currentSize - i - 1; j++) {
			if (comparator(array[j], array[j + 1]) > 0) {
				// Swap array[j] and array[j + 1]
				T temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
				swapped = true;  // Set the flag to true if a swap is made
			}
		}
		// If no swaps were made in this pass, the array is already sorted
		if (!swapped) {
			break;
		}
	}
}





