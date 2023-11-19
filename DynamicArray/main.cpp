#include <iostream>
#include "DynamicArray.cpp"
#include "string"
#include "Person.h"

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
int Compare(T a, T b)
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


int main()
{
	DynamicArray<Person>* da = new DynamicArray<Person>;

	int choice;
	bool work = true;

	while (work) {
		std::cout << "Dynamic Array Menu\n";
		std::cout << "1. Add a new person\n";
		std::cout << "2. Get person by index\n";
		std::cout << "3. Set person by index\n";
		std::cout << "4. Clear the array\n";
		std::cout << "5. Print the array\n";
		std::cout << "6. Bubble Sort the array by age\n"; 
		std::cout << "7. Exit\n";  
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			// Add a new person
		{
			Person newPerson = generateRandomPerson();
			da->addElement(newPerson);
			std::cout << "Person added to the array.\n";
		}
		break;
		case 2:
			// Get person by index
		{
			size_t index;
			std::cout << "Enter index: ";
			std::cin >> index;
			try {
				Person person = da->getElement(index);
				std::cout << "Person at index " << index << ": " << person << "\n";
			}
			catch (const std::out_of_range& e) {
				std::cerr << "Error: " << e.what() << "\n";
			}
		}
		break;
		case 3:
			// Set person by index
		{
			size_t index;
			std::cout << "Enter index: ";
			std::cin >> index;
			try {
				std::string name;
				int age;
				std::string gender;
				std::cout << "Enter new name: ";
				std::cin >> name;
				std::cout << "Enter new age: ";
				std::cin >> age;
				std::cout << "Enter new gender: ";
				std::cin >> gender;

				Person updatedPerson = Person(name, age, gender);
				da->setElement(index, updatedPerson);
				std::cout << "Person at index " << index << " updated.\n";
			}
			catch (const std::out_of_range& e) {
				std::cerr << "Error: " << e.what() << "\n";
			}
		}
		break;
		case 4:
			// Clear the array
			da->clear();
			std::cout << "Array cleared.\n";
			break;
		case 5:
			// Print the array
			std::cout << "Array Contents:\n";
			da->print();
			std::cout << "\n";
			break;
		case 6:
			// Bubble Sort the array by age
		{
			int (*ageComparator)(Person, Person) = [](Person a, Person b)
				{
					return Compare(a.age, b.age);
				};
			da->BubbleSort(ageComparator);
			std::cout << "Array sorted by age using Bubble Sort.\n";
			da->print();
		}
		break;
		case 7:
			// Exit
			work = false;
		default:
			std::cerr << "Invalid choice. Please enter a valid option.\n";
		}
	}

	da->clear();

	const int order = 7;
	const int n = pow(10, order);
	clock_t t1 = clock();
	double max_time_per_element = 0.0;
	for (int i = 0; i < n; i++)
	{
		Person newPerson = generateRandomPerson();
		clock_t t1_element = clock();
		da->addElement(newPerson);
		clock_t t2_element = clock();
		double time_per_element = static_cast<double>(t2_element - t1_element) / CLOCKS_PER_SEC;
		if (time_per_element > max_time_per_element) 
		{
			max_time_per_element = time_per_element;
			std::cout << "New max time per element: " << max_time_per_element << " seconds at index: " << i << std::endl;
		}
	}
	clock_t t2 = clock();
	double total_time = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
	double amortized_time = total_time / n;
	cout << amortized_time;

	da->clear();

	delete da;

	return 0;
}
