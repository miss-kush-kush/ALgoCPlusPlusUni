#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

template<typename T>
struct Node
{
	Node* pNext;
	T data;
	Node(T data = T(), Node* pNext = nullptr)
	{
		this->data = data;
		this->pNext = pNext;
	}
};


template<typename T>
class List
{
public:
	List();
	~List();
	void push_back(T data);//a
	void push_front(T data);//b
	void pop_back();//c
	void pop_front();//d
	void clear();//j
	void print();//k
	T& operator[](const int index);//e// возвращаем ссылку на тип Т для доступа к данным 
	void replaceAt(T data, int index);//f
	int GetSize() { return size; }
	void addAt(T data, int index);//i
	void deleteAt(int index);//h
	Node<T>* searchByData(T data, int(*comparator)(const T&, const T&));//g
	bool deleteByData(T data);//h
	

private:
	int size;
	Node<T>* head;
	void outOfRangeMessage(int index);
};

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
}

template<typename T>
List<T>::~List()
{
	clear();
}

template<typename T>
void List<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else
	{
		Node<T>* current = this->head;
		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node<T>(data);
	}
	size++;
}

template<typename T>
void List<T>::pop_front()
{
	Node<T>* temp = head;//указатель на head. И head и temp имеют один адрес
	head = head->pNext;
	delete temp;//temp указывает на данные, которые были бывшим headом
	size--;
}

template<typename T>
void List<T>::clear()
{
	while (size)//пока переменная больше 0 
	{
		pop_front();
	}
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
T& List<T>::operator[](const int index)
{
	if (index < 0 || index >= size)
	{
		outOfRangeMessage(index);
	}
	//счетчик
	int counter = 0;

	Node<T>* current = this->head; //указатель на текущий елемент
	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}

template<typename T>
void List<T>::push_front(T data)
{
	head = new Node<T>(data, head);
	size++;
}

template<typename T>
void List<T>::pop_back()
{
	deleteAt(size - 1);
}

template<typename T>
void List<T>::replaceAt(T data, int index)
{
	if (index < 0 || index >= size)
	{
		outOfRangeMessage(index);
		return;
	}

	(*this)[index] = data; 
}


template<typename T>
void List<T>::addAt(T data, int index)
{
	if (index == 0)
	{
		push_front(data);
	}
	else
	{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node<T>* newNode = new Node<T>(data, previous->pNext);
		previous->pNext = newNode;
		size++;
	}
}

template<typename T>
void List<T>::deleteAt(int index)
{
	if (index < 0 || index >= size)
	{
		outOfRangeMessage(index);
		return;
	}
	else if(index == 0)
	{
		pop_front();
	}
	else
	{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}
		Node<T>* toDelete = previous->pNext;
		previous->pNext = toDelete->pNext;
		delete toDelete;
		size--;
	}
}

template<typename T>
int compare(const T& a, const T& b) {
	if (a == b) {
		return 0; // Objects are equal
	}
	else if (a < b) {
		return -1; // First object is "smaller" than the second
	}
	else {
		return 1; // First object is "larger" than the second
	}
}

template<typename T>
Node<T>* List<T>::searchByData(T data, int (*comparator)(const T&, const T&)) {
	Node<T>* current = this->head;
	while (current != nullptr) {
		if (comparator(current->data, data) == 0) {
			return current; // Returns a pointer to the found element
		}
		current = current->pNext;
	}
	return nullptr; // Returns NULL in case of failure
}

template<typename T>
bool List<T>::deleteByData(T data)
{
	Node<T>* current = this->head;
	Node<T>* previous = nullptr;

	while (current != nullptr)
	{
		if (current->data == data)
		{
			if (previous == nullptr)
			{
				// The element to delete is the first one (head)
				pop_front();
			}
			else
			{
				previous->pNext = current->pNext;
				delete current;
				size--;
			}
			return true;  // Element found and deleted
		}

		previous = current;
		current = current->pNext;
	}

	return false;  // Element not found
}

int main()
{
	List<int> list;
	int choice;
	Node<int>* foundNode = nullptr; // Declare the variable outside the switch block
	bool deleteSuccess = false; // Declare and initialize deleteSuccess

	do
	{
		cout << "Menu:\n";
		cout << "1. Add an element to the back of the list\n";
		cout << "2. Add an element to the front of the list\n";
		cout << "3. Remove the last element from the list\n";
		cout << "4. Remove the first element from the list\n";
		cout << "5. Clear the list\n";
		cout << "6. Print the list\n";
		cout << "7. Replace an element at a specific index\n";
		cout << "8. Add an element at a specific index\n";
		cout << "9. Delete an element at a specific index\n";
		cout << "10. Search for an element by data\n";
		cout << "11. Delete an element by data\n";
		cout << "0. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			int dataToAddBack;
			cout << "Enter the data to add to the back: ";
			cin >> dataToAddBack;
			list.push_back(dataToAddBack);
			break;
		case 2:
			int dataToAddFront;
			cout << "Enter the data to add to the front: ";
			cin >> dataToAddFront;
			list.push_front(dataToAddFront);
			break;
		case 3:
			list.pop_back();
			break;
		case 4:
			list.pop_front();
			break;
		case 5:
			list.clear();
			break;
		case 6:
			list.print();
			break;
		case 7:
			int indexToReplace;
			int dataToReplace;
			cout << "Enter the index to replace: ";
			cin >> indexToReplace;
			cout << "Enter the data to replace with: ";
			cin >> dataToReplace;
			list.replaceAt(dataToReplace, indexToReplace);
			break;
		case 8:
			int indexToAdd;
			int dataToAdd;
			cout << "Enter the index to add at: ";
			cin >> indexToAdd;
			cout << "Enter the data to add: ";
			cin >> dataToAdd;
			list.addAt(dataToAdd, indexToAdd);
			break;
		case 9:
			int indexToDelete;
			cout << "Enter the index to delete: ";
			cin >> indexToDelete;
			list.deleteAt(indexToDelete);
			break;
		case 10:
			int searchData;
			cout << "Enter the data to search for: ";
			cin >> searchData;
			foundNode = list.searchByData(searchData, compare);
			if (foundNode != nullptr)
			{
				cout << "Found element at address: " << foundNode << endl;
			}
			else
			{
				cout << "Element not found." << endl;
			}
			break;
		case 11:
			int dataToDelete;
			cout << "Enter the data to delete: ";
			cin >> dataToDelete;
			deleteSuccess = list.deleteByData(dataToDelete);
			if (deleteSuccess)
			{
				cout << "Successfully deleted element." << endl;
			}
			else
			{
				cout << "Element not found." << endl;
			}
			break;
		case 0:
			cout << "Exiting the program." << endl;
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
			break;
		}
	} while (choice != 0);

	const int MAX_ORDER = 4;

	for (int o = 1; o <= MAX_ORDER; o++) 
	{
		const int n = pow(10, o); 
		auto start = high_resolution_clock::now();
		for (int i = 0; i < n; i++) {
			list.push_back(rand() % 20);
		}
		auto end = high_resolution_clock::now();

		duration<double, milli> duration = end - start;
		cout << "For n=" << n << ", time taken: " << duration.count() << " ms" << std::endl;
		
	}

	return 0;
}

