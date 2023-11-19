#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath> 
#include "BSTree.h"
using namespace std;

#include <map>
#include <vector>
#include <numeric>
#include <algorithm>

#include "BSTNode.h"
template <typename T>
class BSTree {
public:
    BSTree() : root(nullptr), size(0) {}

    T get_min_node_data()
    {
        return findMin(root)->data;
    }

    void insert(T data) {
        root = insertRecursive(root, data);
        size++;
    }//a
    BSTNode<T>* search(T data) {
        return searchIterative(root, data);
    }//b
    void remove(BSTNode<T>* node) {
        root = removeRecursive(root, node);
        size--;
    }//c


    int height() {
        return calculateHeight(root);
    }//g

    void printTree(bool preorder) {
        if (preorder) {
            std::cout << "binary search tree (preorder):" << std::endl;
            std::cout << "size: " << size << std::endl;
            std::cout << "height: " << height() << std::endl;
            preorderTraversal(root);
        }
        else {
            std::cout << "binary search tree (inorder):" << std::endl;
            std::cout << "size: " << size << std::endl;
            std::cout << "height: " << height() << std::endl;
            inorderTraversal(root);
        }
    }//h

    ~BSTree() {
        cleanTree(root);
    }
private:
    BSTNode<T>* root;
    int size;

    BSTNode<T>* insertRecursive(BSTNode<T>* node, T data) {
        if (node == nullptr) {
            int newIndex = size; // You can assign unique indices as per your requirement
            return new BSTNode<T>(data, newIndex);
        }

        if (data < node->data) {
            node->left = insertRecursive(node->left, data);
            node->left->parent = node;
        }
        else if (data > node->data) {
            node->right = insertRecursive(node->right, data);
            node->right->parent = node;
        }

        return node;
    }

    template <typename T>
    BSTNode<T>* searchIterative(BSTNode<T>* node, T data) {
        BSTNode<T>* current = node;

        while (current != nullptr) {
            if (data == current->data) {
                return current;  // Element found
            }
            else if (data < current->data) {
                current = current->left;  // Search in the left subtree
            }
            else {
                current = current->right;  // Search in the right subtree
            }
        }

        return nullptr;  // Element not found
    }


    BSTNode<T>* findMin(BSTNode<T>* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    BSTNode<T>* removeRecursive(BSTNode<T>* node, BSTNode<T>* toRemove) {
        BSTNode<T>* temp;
        if (node == nullptr) {
            return node;
        }

        if (toRemove->data < node->data) {
            node->left = removeRecursive(node->left, toRemove);
        }
        else if (toRemove->data > node->data) {
            node->right = removeRecursive(node->right, toRemove);
        }
        else {
            if (node->left == nullptr) {
                temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                temp = node->left;
                delete node;
                return temp;
            }

            temp = findMin(node->right);
            node->data = temp->data;
            node->right = removeRecursive(node->right, temp);
        }

        return node;
    }

    int calculateHeight(BSTNode<T>* node) {
        if (node == nullptr) {
            return 0;
        }
        else
        {
            int leftHeight = calculateHeight(node->left);
            int rightHeight = calculateHeight(node->right);
            if (leftHeight > rightHeight)
            {
                return (leftHeight + 1);
            }
            else
                return (rightHeight + 1);
        }
     
    }

    void inorderTraversal(BSTNode<T>* node) {//e
        if (node == nullptr) {
            return;
        }

        inorderTraversal(node->left);
        std::cout << "{ (" << node->index << ": [p: ";
        if (node->parent) {
            std::cout << node->parent->index;
        }
        else {
            std::cout << "NULL";
        }
        std::cout << ", l: ";
        if (node->left) {
            std::cout << node->left->index;
        }
        else {
            std::cout << "NULL";
        }
        std::cout << ", r: ";
        if (node->right) {
            std::cout << node->right->index;
        }
        else {
            std::cout << "NULL";
        }
        std::cout << "], data: " << node->data << "), " << std::endl;
        inorderTraversal(node->right);
    }

    void preorderTraversal(BSTNode<T>* node) {//d
        if (node == nullptr) {
            return;
        }

        std::cout << "{ (" << node->index << ": [p: ";
        if (node->parent) {
            std::cout << node->parent->index;
        }
        else {
            std::cout << "NULL";
        }
        std::cout << ", l: ";
        if (node->left) {
            std::cout << node->left->index;
        }
        else {
            std::cout << "NULL";
        }
        std::cout << ", r: ";
        if (node->right) {
            std::cout << node->right->index;
        }
        else {
            std::cout << "NULL";
        }
        std::cout << "], data: " << node->data << "), " << std::endl;
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }

    
    void cleanTree(BSTNode<T>* node) {
        if (node == nullptr) {
            return;
        }
        cleanTree(node->left);
        cleanTree(node->right);
        delete node;
        
    }
};



void test()
{
    std::vector<int> v(8);
    std::iota(v.begin(), v.end(), 0);
    std::map<int, int> heights, min_node_data;
    do
    {
        BSTree<int> t;
        for (int i : v)
            t.insert(i);
        ++heights[t.height()];
        for (int i : v)
        {
            ++min_node_data[t.get_min_node_data()];
            t.remove(t.search(i));
        }
    } while (std::next_permutation(v.begin(), v.end()));
    for (auto [height, cnt] : heights)
        std::cout << height << ": " << cnt << std::endl;
    std::cout << "***" << std::endl;
    for (auto [data, cnt] : min_node_data)
        std::cout << data << ": " << cnt << std::endl;
}

int main() {
    test();
    return 0;
    BSTree<int> bst1;
    BSTNode<int>* node;

    int inputData[] = { 10, 15, 12, 5, 30, 25, 35, 7, -2, 33 };

    for (int i = 0; i < 10; i++) {
        bst1.insert(inputData[i]);
    }

    bool work = true;
    int choice;
    while (work) {
        cout << "Choose an option:" << endl;
        cout << "1. Search" << endl;
        cout << "2. Remove" << endl;
        cout << "3. Print Preorder" << endl;
        cout << "4. Print Inorder" << endl;
        cout << "5. Exit" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
        {
            int data;
            cout << "Enter data to search: ";
            cin >> data;
            node = bst1.search(data);
            if (node) {
                cout << "Data found in the tree." << endl;
            }
            else {
                cout << "Data not found in the tree." << endl;
            }
        }
        break;
        case 2:
        {
            int data;
            cout << "Enter data to remove: ";
            cin >> data;
            node = bst1.search(data);
            if (node) {
                cout << "Found the node with data " << node->data << ". Deleting it." << endl;
                bst1.remove(node);
            }
            else {
                cout << "Data not found in the tree." << endl;
            }
        }
        break;
        case 3:
            bst1.printTree(true); // Print in preorder
            break;
        case 4:
            bst1.printTree(false); // Print in inorder
            break;
        case 5:
            work = false;
        default:
            cout << endl;
        }
    }
   
    const int MAX_ORDER = 7;
    BSTree<int>* bst = new BSTree<int>();

    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10, o); // Size of data

        // Adding data to the tree
        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            int data = rand() % n; // Generate random data (int)
            bst->insert(data);
        }
        clock_t t2 = clock();
        // Output tree and timing measurements
        double timeToAdd = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
        cout << "Time to add " << n << " elements: " << timeToAdd << " seconds" << endl;

        // Searching
        const int m = pow(10, 4); // Number of search attempts
        int hits = 0; // Number of hits

        t1 = clock();
        for (int i = 0; i < m; i++) {
            int data = rand() % n; // Generate random data for search
            node = bst->search(data);
            if (node) {
                int result = node->data;
                if (result != 0) {
                    hits++;
                }
            }
            
        }
        t2 = clock();
        // Output timing measurements and number of hits
        double timeToSearch = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
        cout << "Time to search " << m << " elements: " << timeToSearch << " seconds" << endl;
    }
    delete bst;

    return 0;
}
