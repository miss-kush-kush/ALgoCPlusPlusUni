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
