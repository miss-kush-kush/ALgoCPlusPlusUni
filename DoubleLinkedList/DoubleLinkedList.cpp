#include <iostream>
#include <string>
#include <chrono>
#include "List.cpp"
using namespace std;
using namespace chrono;

int main()
{
    List<int> list;
    int choice;
    Node<int>* foundNode = nullptr;
    bool deleteSuccess = false;

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
        cout << "8. Add an element at a specific index and sort it\n";
        cout << "9. Delete an element at a specific index\n";
        cout << "10. Search for an element by data\n";
        cout << "11. Delete an element by data\n";
        cout << "12. Clear screen\n";
        cout << "13. Create List with 10 elements print\n";
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
            list.print();

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
            foundNode = list.searchByData(searchData);
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
        case 12:
            system("CLS");
            break;
        case 13:
            list.clear();
            for (int i = 10; i > 0; --i) {
                list.push_back(i);
            }
            cout << "List created with 10 random elements: ";
            list.print();
            break;
        case 0:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != 0);

    list.clear();
    const int MAX_ORDER = 6;

    for (int o = 1; o <= MAX_ORDER; o++)
    {
        cout << "Adding elements"<<endl;
        const int n = pow(10, o);
        auto start = high_resolution_clock::now();
        for (int i = 0; i < n; i++) {
            list.push_back(rand() % 1000000);
        }
        auto end = high_resolution_clock::now();

        duration<double, milli> duration = end - start;
        cout << "For n=" << n << ", time taken: " << duration.count() << " ms" << endl;

        cout << "Searching element"<<endl;
        const int m = pow(10, 4); 
        start = high_resolution_clock::now();
        for (int i = 0; i < m; i++) {
            int data = rand() % 1000000;
            deleteSuccess = list.deleteByData(data);
        }
        if (deleteSuccess)
        {
            cout << "Successfully deleted element." << endl;
        }
        else
        {
            cout << "Element not found." << endl;
        }
        end = high_resolution_clock::now();
        cout << "For n=" << n << ", time taken: " << duration.count() << " ms" << endl;
    }

    return 0;
}
