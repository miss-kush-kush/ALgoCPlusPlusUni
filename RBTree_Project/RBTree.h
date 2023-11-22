#include "RBNode.h"
enum TraversalOrder { PREORDER, INORDER };
enum Direction { LEFT, RIGHT };

template <typename Key>
class RedBlackTree {
public:
    RedBlackTree() : root(nullptr), size(0) {}
    ~RedBlackTree()
    {
        clear();
    }

    // Funkcje interfejsu
    RBNode<Key>* search(const Key& key);
    std::string preOrderToStringRecursive(RBNode<Key>* node);
    std::string inOrderToStringRecursive(RBNode<Key>* node);
    void clear();
    int getHeight();
    void insert(const Key& key);
    std::string toString(TraversalOrder order);
    Key get_root_data() const {
        if (root != nullptr)
            return root->key;
        else
            throw std::runtime_error("Tree is empty");
    }

private:
    // Funkcje pomocnicze
    void Rotate(RBNode<Key>* node, Direction direction);
    void ReArrange(RBNode<Key>* node);
    void clearRecursive(RBNode<Key>* node);
    int heightRecursive(RBNode<Key>* node);

    // Pole przechowujące korzeń drzewa
    RBNode<Key>* root;

    // Pole przechowujące aktualny rozmiar drzewa
    int size;
};

