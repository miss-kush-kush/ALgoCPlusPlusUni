#include "MaxHeap.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

template <typename T>
using KeyFunction = double (*)(T);

template <typename T>
using ComparatorFunction = int (*)(T, T);

void counting_sort(int* array, int n, int m) {
    int* count = new int[m]();

    for (int i = 0; i < n; i++) {
        count[array[i]]++;
    }

    int index = 0;
    for (int i = 0; i < m; i++) {
        while (count[i] > 0) {
            array[index] = i;
            index++;
            count[i]--;
        }
    }

    delete[] count;
}

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}


template <typename T>
void merge(vector<T>& arr, int left, int mid, int right, ComparatorFunction<T> comparator) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<T> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (comparator(L[i], R[j]) <= 0) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

template <typename T>
void mergeSort(vector<T>& arr, int left, int right, ComparatorFunction<T> comparator) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, comparator);
    mergeSort(arr, mid + 1, right, comparator);
    merge(arr, left, mid, right, comparator);
}


void bucket_sort(int* array, int n, int m) {
    int num_buckets = n; // Number of buckets
    vector<vector<int>> buckets(num_buckets);

    // Distribute elements into buckets
    for (int i = 0; i < n; i++) {
        int index = static_cast<int>((static_cast<double>(array[i]) / m) * n);
        buckets[index].push_back(array[i]);
    }

    // Sort each bucket using merge sort
    for (int i = 0; i < num_buckets; i++) {
        if (!buckets[i].empty()) {
            mergeSort(buckets[i], 0, buckets[i].size() - 1);
        }
    }

    // Concatenation
    int idx = 0;
    for (auto& bucket : buckets) {
        for (int num : bucket) {
            array[idx++] = num;
        }
    }
}


template <typename T>
void bucket_sort(T* array, int n, double m, KeyFunction<T> keyFunction, ComparatorFunction<T> comparator) {
    int num_buckets = n; // Number of buckets
    vector<vector<T>> buckets(num_buckets);

    // Distribute elements into buckets
    for (int i = 0; i < n; i++) {
        int index = static_cast<int>(keyFunction(array[i]) * n);
        buckets[index].push_back(array[i]);
    }

    // Sort each bucket
    for (int i = 0; i < num_buckets; i++) {
        mergeSort(buckets[i], 0, buckets[i].size() - 1, comparator);
    }

    int idx = 0;
    for (auto& bucket : buckets) {
        for (T element : bucket) {
            array[idx++] = element;
        }
    }
}



class Person {
public:
    string name;
    int age;
    string gender;

    Person() {
        age = 20;
        name = "Liza";
        gender = "female";
    }

    Person(const string& _name, int _age, const string& _gender)
        : name(_name), age(_age), gender(_gender) {}

    friend ostream& operator<<(ostream& os, const Person& person) {
        os << "Name: " << person.name << ", Age: " << person.age << ", Gender: " << person.gender;
        return os;
    }
};

void printArray(Person** array, int n) {
    for (int i = 0; i < n; i++) {
        cout << *array[i] << endl;
    }
}

const string maleNames[] = { "John", "Michael", "Robert", "William", "James" };
const string femaleNames[] = { "Mary", "Jennifer", "Linda", "Patricia", "Elizabeth" };
const string genders[] = { "Male", "Female" };

Person generateRandomPerson() {
    string name, gender;
    int age;

    if (rand() % 2 == 0) {
        name = maleNames[rand() % 5];
        gender = "Male";
    }
    else {
        name = femaleNames[rand() % 5];
        gender = "Female";
    }

    age = rand() % 120;

    return Person(name, age, gender);
}

int ageComparator(Person* a, Person* b) {
    return comparator(a->age, b->age);
}


double personKey(Person* p) {
    return static_cast<double>(p->age) / 1000.0;
}

bool arePersonArraysEqual(Person** arr1, Person** arr2, int n) {
    for (int i = 0; i < n; i++) {
        if (arr1[i]->name != arr2[i]->name || arr1[i]->age != arr2[i]->age || arr1[i]->gender != arr2[i]->gender) {
            return false;
        }
    }
    return true;
}

bool areArraysEqual(int* arr1, int* arr2, int n) {
    for (int i = 0; i < n; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

void main_ints() {
    srand(0);
    const int MAX_ORDER = 1;
    const int m = static_cast<int>(pow(10, 7));

    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = static_cast<int>(pow(10, o));
        int* array1 = new int[n];

        // Populate and print the initial array1
        cout << "Initial array1: [";
        for (int i = 0; i < n; i++) {
            array1[i] = rand() % m; // Generate random integer between 0 and m-1
            cout << array1[i] << (i < n - 1 ? ", " : "");
        }
        cout << "]\n";

        // Create copies of array1 into array2 and array3
        int* array2 = new int[n];
        int* array3 = new int[n];
        memcpy(array2, array1, n * sizeof(int));
        memcpy(array3, array1, n * sizeof(int));

        // Perform sorting on array1 using counting_sort and print
        clock_t t1 = clock();
        counting_sort(array1, n, m);
        clock_t t2 = clock();
        double countingSortTime = (static_cast<double>(t2 - t1) / CLOCKS_PER_SEC);
        cout << "Array1 after counting sort: [";
        for (int i = 0; i < n; i++) {
            cout << array1[i] << (i < n - 1 ? ", " : "");
        }
        cout << "]\n";

        // Perform sorting on array2 using heap_sort and print
        t1 = clock();
        MaxHeap<int>* bh = new MaxHeap<int>(array2, n, comparator, true);
        bh->heap_sort(comparator);
        t2 = clock();
        double heapSortTime = (static_cast<double>(t2 - t1) / CLOCKS_PER_SEC);
        cout << "Array2 after heap sort: [";
        for (int i = 0; i < n; i++) {
            cout << array2[i] << (i < n - 1 ? ", " : "");
        }
        cout << "]\n";

        // Perform sorting on array3 using bucket_sort and print
        t1 = clock();
        bucket_sort(array3, n, m);
        t2 = clock();
        double bucketSortTime = (static_cast<double>(t2 - t1) / CLOCKS_PER_SEC);
        cout << "Array3 after bucket sort: [";
        for (int i = 0; i < n; i++) {
            cout << array3[i] << (i < n - 1 ? ", " : "");
        }
        cout << "]\n";

        // Print sorting times
        cout << "Array Size: " << n << endl;
        cout << "Counting Sort Time: " << countingSortTime << " seconds" << endl;
        cout << "Heap Sort Time: " << heapSortTime << " seconds" << endl;
        cout << "Bucket Sort Time: " << bucketSortTime << " seconds" << endl;
        if (areArraysEqual(array1, array2, n) && areArraysEqual(array2, array3, n)) {
            cout << "\nThe sorting is done correctly\n";
        }
        else {
            cout << "\nOne of the sorting methods is incorrect";
        }
        // Free memory
        delete[] array1;
        delete[] array2;
        delete[] array3;
    }
}


void main_some_objects() {
    const int MAX_ORDER = 1;
    const double m_double = static_cast<double>(pow(2, 30));

    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = static_cast<int>(pow(10, o));
        Person** array1 = new Person * [n];

        for (int i = 0; i < n; i++) {
            array1[i] = new Person(generateRandomPerson());
        }

        // Print initial array
        cout << "Initial Array:" << endl;
        printArray(array1, n);

        Person** array2 = new Person * [n];
        memcpy(array2, array1, n * sizeof(Person*)); // Create a copy

        // Heap Sort
        clock_t t1 = clock();
        MaxHeap<Person*>* bh = new MaxHeap<Person*>(array1, n, ageComparator, true);
        bh->heap_sort(ageComparator);
        clock_t t2 = clock();
        double heapSortTime = (static_cast<double>(t2 - t1) / CLOCKS_PER_SEC);

        // Print array after Heap Sort
        cout << "Array after Heap Sort:" << endl;
        printArray(array1, n);

        // Bucket Sort
        t1 = clock();
        bucket_sort<Person*>(array2, n, 1.0, personKey, ageComparator);
        t2 = clock();
        double bucketSortTime = (static_cast<double>(t2 - t1) / CLOCKS_PER_SEC);

        // Print array after Bucket Sort
        cout << "Array after Bucket Sort:" << endl;
        printArray(array2, n);

        cout << "Array Size: " << n << endl;
        cout << "Heap Sort Time: " << heapSortTime << " seconds" << endl;
        cout << "Bucket Sort Time: " << bucketSortTime << " seconds" << endl;

        if (arePersonArraysEqual(array1, array2, n)) {
            cout << "\nThe sorting is done correctly";
        }
        else {
            cout << "\nOne of the sorting methods is incorrect";
        }

        // Cleanup
        for (int i = 0; i < n; i++) {
            delete array1[i];
            delete array2[i];
        }
        delete[] array1;
        delete[] array2;
    }
}

int main() {
    main_ints();
    main_some_objects();

    return 0;
}