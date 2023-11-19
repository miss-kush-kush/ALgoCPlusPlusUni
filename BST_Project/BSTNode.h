#include <iostream>
#include <cstdlib>
#include <string>

template <class T>
class BSTNode {
public:
    T data;
    BSTNode* parent;
    BSTNode* left;
    BSTNode* right;
    int index;

    BSTNode(T value, int idx) : data(value), parent(nullptr), left(nullptr), right(nullptr), index(idx) {}
};