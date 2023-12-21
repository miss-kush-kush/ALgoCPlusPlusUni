#include <iostream>
#include <climits>
#include <functional> 
using namespace std;

template<typename T>
class MaxHeap
{
private:
	T* heapArr;
	int maxSize;
	int heapSize;

	void swap(T* x, T* y);
	void heapifyUp(int i, int(*comparator)(T, T));
	void heapifyDown(int i, int(*comparator)(T, T));
public:
	MaxHeap()
	{
		heapSize = 0;
		maxSize = 1;
		heapArr = new T[maxSize];
	};
	~MaxHeap()
	{
		delete[] heapArr;
	};

	int size() const { return heapSize; }

	void insert(T data, int (*comparator)(T, T));
	T removeMax_Root(int (*comparator)(T, T));
	void clear();
	void print();
	void resizeHeap();

	MaxHeap(T* array, int size, int (*comparator)(T, T), bool topDown);


	void heap_sort(int(*comparator)(T, T));

};

template<typename T>
MaxHeap<T>::MaxHeap(T* array, int size, int (*comparator)(T, T), bool bottomUp) {
	heapArr = array;
	maxSize = size;
	heapSize = size;
	if (bottomUp) {
		for (int i = (heapSize / 2) - 1; i >= 0; i--) {
			heapifyDown(i, comparator);
		}
	}
	else {
		for (int i = 1; i < heapSize; i++) {
			heapifyUp(i, comparator);
		}
	}
}

template<typename T>
void MaxHeap<T>::heap_sort(int (*comparator)(T, T)) {
	for (int i = heapSize - 1; i >= 0; i--) {
		swap(&heapArr[0], &heapArr[i]);
		heapSize--;
		heapifyDown(0, comparator);
	}
	heapSize = maxSize;
}

template<typename T>
inline void MaxHeap<T>::swap(T* x, T* y)
{
	T temp = *x;
	*x = *y;
	*y = temp;
}

template<typename T>
inline void MaxHeap<T>::heapifyUp(int i, int(*comparator)(T, T))
{
	int parentIndex = (i - 1) / 2;
	if (i != 0 && comparator(heapArr[i], heapArr[parentIndex]) > 0)
	{
		swap(&heapArr[i], &heapArr[parentIndex]);
		heapifyUp(parentIndex, comparator);
	}
}

template<typename T>
inline void MaxHeap<T>::heapifyDown(int i, int(*comparator)(T, T))
{
	int leftChild = (2 * i) + 1;
	int rightChild = (2 * i) + 2;
	int largest = i;

	if (leftChild < heapSize && comparator(heapArr[leftChild], heapArr[largest]) > 0)
		largest = leftChild;

	if (rightChild < heapSize && comparator(heapArr[rightChild], heapArr[largest]) > 0)
		largest = rightChild;

	if (largest != i) {
		swap(&heapArr[i], &heapArr[largest]);
		heapifyDown(largest, comparator);
	}
}


template<typename T>
inline void MaxHeap<T>::insert(T data, int(*comparator)(T, T))
{
	if (heapSize == maxSize) {
		resizeHeap();
	}

	heapSize++;
	int i = heapSize - 1;
	heapArr[i] = data;

	heapifyUp(i, comparator);
}

template<typename T>
inline T MaxHeap<T>::removeMax_Root(int(*comparator)(T, T))
{
	if (heapSize <= 0) {
		cout << ("\nHeap is empty\n");
	}
	if (heapSize == 1)
	{
		heapSize--;
		return heapArr[0];
	}


	T root = heapArr[0];
	heapArr[0] = heapArr[heapSize - 1];
	heapSize--;

	heapifyDown(0, comparator);

	return root;
}


template<typename T>
inline void MaxHeap<T>::clear()
{
	delete[] heapArr;
	maxSize = 1;
	heapSize = 0;
	heapArr = new T[maxSize];
}

template<typename T>
inline void MaxHeap<T>::print()
{
	cout << "[ ";
	for (int i = 0; i < heapSize; ++i) {
		cout << (heapArr[i]) << ", ";
	}
	cout << "]";
}

template<typename T>
inline void MaxHeap<T>::resizeHeap()
{
	maxSize *= 2;
	T* newHeapArr = new T[maxSize];
	for (int i = 0; i < heapSize; ++i) {
		newHeapArr[i] = heapArr[i];
	}
	delete[] heapArr;
	heapArr = newHeapArr;
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