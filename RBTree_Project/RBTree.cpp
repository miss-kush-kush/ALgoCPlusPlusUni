#include "RBTree.h"

template <typename Key>
RBNode<Key>* RedBlackTree<Key>::search(const Key& key) {
    RBNode<Key>* current = root;

    // Traverse the tree until the key is found or reach a leaf node
    while (current != nullptr) {
        if (key == current->key) {
            // Key found
            return current;
        }
        else if (key < current->key) {
            // Go left
            current = current->left;
        }
        else {
            // Go right
            current = current->right;
        }
    }

    // Key not found
    return nullptr;
}

template <typename Key>
std::string RedBlackTree<Key>::preOrderToStringRecursive(RBNode<Key>* node) {
    std::stringstream result;

    if (node != nullptr) {
        result << "(" << node->index << ": [" << (node->color == Color::RED ? "red" : "black")
            << ", p: " << (node->parent ? std::to_string(node->parent->index) : "NULL")
            << ", l: " << (node->left ? std::to_string(node->left->index) : "NULL")
            << ", r: " << (node->right ? std::to_string(node->right->index) : "NULL") << "] ("
            << node->key << ")) \n";

        result << preOrderToStringRecursive(node->left);
        result << preOrderToStringRecursive(node->right);
    }

    return result.str();
}

template <typename Key>
std::string RedBlackTree<Key>::inOrderToStringRecursive(RBNode<Key>* node) {
    std::stringstream result;

    if (node != nullptr) {
        result << inOrderToStringRecursive(node->left);
        result << "(" << node->index << ": [" << (node->color == Color::RED ? "red" : "black")
            << ", p: " << (node->parent ? std::to_string(node->parent->index) : "NULL")
            << ", l: " << (node->left ? std::to_string(node->left->index) : "NULL")
            << ", r: " << (node->right ? std::to_string(node->right->index) : "NULL") << "] ("
            << node->key << ")) \n";
        result << inOrderToStringRecursive(node->right);
    }

    return result.str();
}

template <typename Key>
void RedBlackTree<Key>::clear() {
    clearRecursive(root);
    root = nullptr;
    size = 0;
}

template <typename Key>
void RedBlackTree<Key>::clearRecursive(RBNode<Key>* node) {
    if (node != nullptr) {
        // Recursively clear the left and right subtrees
        clearRecursive(node->left);
        clearRecursive(node->right);

        // Delete the current node
        delete node;
    }
}

template <typename Key>
int RedBlackTree<Key>::getHeight() {
    return heightRecursive(root);
}

template <typename Key>
int RedBlackTree<Key>::heightRecursive(RBNode<Key>* node) {
    if (node == nullptr) {
        // Height of an empty tree is -1
        return -1;
    }

    // Recursively compute the height of the left and right subtrees
    int leftHeight = heightRecursive(node->left);
    int rightHeight = heightRecursive(node->right);

    // Return the maximum height plus 1
    return std::max(leftHeight, rightHeight) + 1;
}

template <typename Key>
std::string RedBlackTree<Key>::toString(TraversalOrder order) {
    return (order == TraversalOrder::PREORDER) ? preOrderToStringRecursive(root) : inOrderToStringRecursive(root);
}

template <typename Key>
void RedBlackTree<Key>::insert(const Key& key) {
    RBNode<Key>* newNode = new RBNode<Key>(key, Color::RED);

    // Perform a regular BST insert
    RBNode<Key>* y = nullptr;
    RBNode<Key>* x = root;

    while (x != nullptr) {
        y = x;
        if (newNode->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    newNode->parent = y;
    if (y == nullptr)
        root = newNode;
    else if (newNode->key < y->key)
        y->left = newNode;
    else
        y->right = newNode;

    // Set the index for the new node
    newNode->index = size;

    // Fix the tree
    ReArrange(newNode);
    size++;
}


template <typename Key>
void RedBlackTree<Key>::Rotate(RBNode<Key>* node, Direction direction)
{
    if (direction == Direction::RIGHT)
    {
        RBNode<Key>* x = node->left;
        node->left = x->right;

        if (x->right != nullptr)
            x->right->parent = node;

        x->parent = node->parent;

        if (node->parent == nullptr)
            root = x;
        else if (node == node->parent->left)
            node->parent->left = x;
        else
            node->parent->right = x;

        x->right = node;
        node->parent = x;
    }
    if (direction == Direction::LEFT)
    {
        RBNode<Key>* y = node->right;
        node->right = y->left;

        if (y->left != nullptr)
            y->left->parent = node;

        y->parent = node->parent;

        if (node->parent == nullptr)
            root = y;
        else if (node == node->parent->left)
            node->parent->left = y;
        else
            node->parent->right = y;

        y->left = node;
        node->parent = y;
    }

}

template <typename Key>
void RedBlackTree<Key>::ReArrange(RBNode<Key>* z) {
    while (z != nullptr && z->parent != nullptr && z->parent->color == Color::RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode<Key>* y = z->parent->parent->right;
            if (y != nullptr && y->color == Color::RED) {
                z->parent->color = Color::BLACK;
                y->color = Color::BLACK;
                z->parent->parent->color = Color::RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    Rotate(z, Direction::LEFT);
                }

                z->parent->color = Color::BLACK;
                z->parent->parent->color = Color::RED;
                Rotate(z->parent->parent, Direction::RIGHT);
            }
        }
        else {
            // Symmetric case with left and right exchanged
            RBNode<Key>* y = z->parent->parent->left;
            if (y != nullptr && y->color == Color::RED) {
                z->parent->color = Color::BLACK;
                y->color = Color::BLACK;
                z->parent->parent->color = Color::RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    Rotate(z, Direction::RIGHT);
                }

                z->parent->color = Color::BLACK;
                z->parent->parent->color = Color::RED;
                Rotate(z->parent->parent, Direction::LEFT);
            }
        }
    }

    // Ensure that the root is black
    root->color = Color::BLACK;
}

