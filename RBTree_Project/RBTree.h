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
    void clear();
    int height();
    void insert(const Key& key);
    void Display(TraversalOrder order);
    Key get_root_data() const {
        if (root != nullptr)
            return root->key;
        else
            throw runtime_error("Tree is empty");
    }

private:
    // Funkcje pomocnicze
    void Rotate(RBNode<Key>* node, Direction direction);
    void ReArrange(RBNode<Key>* node);
    void clearRecursive(RBNode<Key>* node);
    int heightRecursive(RBNode<Key>* node);

    void Print(RBNode<Key>* node);
    void preOrderToStringRecursive(RBNode<Key>* node);
    void inOrderToStringRecursive(RBNode<Key>* node);

    // Pole przechowujące korzeń drzewa
    RBNode<Key>* root;

    // Pole przechowujące aktualny rozmiar drzewa
    int size;
};

// Wyszukiwanie węzła o określonym kluczu w drzewie czerwono-czarnym
template <typename Key>
RBNode<Key>* RedBlackTree<Key>::search(const Key& key) {
    RBNode<Key>* current = root;

    // Przechodzenie drzewa do momentu znalezienia klucza lub dotarcia do liścia
    while (current != nullptr) {
        if (key == current->key) {
            // Klucz znaleziony
            return current;
        }
        else if (key < current->key) {
            // Idź w lewo
            current = current->left;
        }
        else {
            // Idź w prawo
            current = current->right;
        }
    }

    // Klucz nie znaleziony
    return nullptr;
}

// Wyświetlanie drzewa czerwono-czarnego w określonej kolejności przechodzenia
template <typename Key>
void RedBlackTree<Key>::Display(TraversalOrder order) {
    return (order == TraversalOrder::PREORDER) ? preOrderToStringRecursive(root) : inOrderToStringRecursive(root);
}

// Wyświetlanie informacji o węźle (indeks, kolor, rodzic, lewy i prawy potomek, klucz)
template <typename Key>
void RedBlackTree<Key>::Print(RBNode<Key>* node) {
    cout << "(" << node->index << ": [" << (node->color == Color::RED ? "red" : "black")
        << ", p: " << (node->parent ? to_string(node->parent->index) : "NULL")
        << ", l: " << (node->left ? to_string(node->left->index) : "NULL")
        << ", r: " << (node->right ? to_string(node->right->index) : "NULL") << "] ("
        << node->key << ")) \n";
}

// Rekurencyjna funkcja wyświetlająca drzewo czerwono-czarne w porządku pre-order
template <typename Key>
void RedBlackTree<Key>::preOrderToStringRecursive(RBNode<Key>* node) {
    stringstream result;

    if (node != nullptr) {
        Print(node);
        preOrderToStringRecursive(node->left);
        preOrderToStringRecursive(node->right);
    }
}

// Rekurencyjna funkcja wyświetlająca drzewo czerwono-czarne w porządku in-order
template <typename Key>
void RedBlackTree<Key>::inOrderToStringRecursive(RBNode<Key>* node) {
    stringstream result;

    if (node != nullptr) {
        inOrderToStringRecursive(node->left);
        Print(node);
        inOrderToStringRecursive(node->right);
    }
}

// Czyszczenie drzewa czerwono-czarnego
template <typename Key>
void RedBlackTree<Key>::clear() {
    clearRecursive(root);
    root = nullptr;
    size = 0;
}

// Rekurencyjna funkcja czyszcząca drzewo czerwono-czarne
template <typename Key>
void RedBlackTree<Key>::clearRecursive(RBNode<Key>* node) {
    if (node != nullptr) {
        // Rekurencyjne czyszczenie lewego i prawego poddrzewa
        clearRecursive(node->left);
        clearRecursive(node->right);

        // Usunięcie bieżącego węzła
        delete node;
    }
}

// Obliczanie wysokości drzewa czerwono-czarnego
template <typename Key>
int RedBlackTree<Key>::height() {
    return heightRecursive(root);
}

// Rekurencyjna funkcja obliczająca wysokość drzewa czerwono-czarnego
template <typename Key>
int RedBlackTree<Key>::heightRecursive(RBNode<Key>* node) {
    if (node == nullptr) {
        // Węzeł pusty, zwracamy 0 (brak wysokości).
        return 0;
    }
    else {
        // Oblicz wysokość lewego i prawego poddrzewa rekurencyjnie.
        int leftHeight = heightRecursive(node->left);
        int rightHeight = heightRecursive(node->right);

        // Jeśli bieżący węzeł jest czarny, dodajemy 1 do wysokości; w przeciwnym razie 0.
        int currentNodeHeight = (node->color == Color::BLACK) ? 1 : 0;

        // Zwracamy maksimum z wysokości lewego i prawego poddrzewa, dodając ewentualnie 1 z bieżącego węzła.
        return max(leftHeight, rightHeight) + currentNodeHeight;
    }
}

// Wstawianie nowego klucza do drzewa czerwono-czarnego
template <typename Key>
void RedBlackTree<Key>::insert(const Key& key) {
    RBNode<Key>* newNode = new RBNode<Key>(key, Color::RED);

    // Wykonaj standardowe wstawianie w BST
    RBNode<Key>* parentOfNewNode = nullptr;
    RBNode<Key>* currentNode = root;

    // Przeszukiwanie drzewa w celu znalezienia odpowiedniego miejsca dla nowego węzła
    while (currentNode != nullptr) {
        parentOfNewNode = currentNode; // Aktualizacja rodzica nowego węzła przed przesunięciem w dół drzewa

        if (newNode->key < currentNode->key)
            currentNode = currentNode->left; // Idź w lewo, jeśli nowy klucz jest mniejszy
        else
            currentNode = currentNode->right; // Idź w prawo, jeśli nowy klucz jest większy
    }

    // Ustaw rodzica nowego węzła
    newNode->parent = parentOfNewNode;

    if (parentOfNewNode == nullptr)
        root = newNode; // Nowy węzeł staje się korzeniem, jeśli drzewo było puste
    else if (newNode->key < parentOfNewNode->key)
        parentOfNewNode->left = newNode;
    else
        parentOfNewNode->right = newNode;

    // Ustaw indeks dla nowego węzła
    newNode->index = size;

    // Napraw drzewo po wstawieniu nowego węzła
    ReArrange(newNode);

    size++; // Zwiększ rozmiar drzewa
}


// Rotacja węzła w określonym kierunku (lewo/prawo)
template <typename Key>
void RedBlackTree<Key>::Rotate(RBNode<Key>* node, Direction direction) {
    RBNode<Key>* child = (direction == Direction::LEFT) ? node->right : node->left;

    if (child != nullptr) {
        // Zaktualizuj rodzica dziecka
        child->parent = node->parent;

        // Zaktualizuj wskaźnik dziecka rodzica węzła
        if (node->parent == nullptr)
            root = child;
        else if (node == node->parent->left)
            node->parent->left = child;
        else
            node->parent->right = child;
    }

    if (direction == Direction::LEFT) {
        // Rotacja w lewo
        node->right = (child != nullptr) ? child->left : nullptr;

        if (node->right != nullptr)
            node->right->parent = node;

        if (child != nullptr)
            child->left = node;
    }
    else {
        // Rotacja w prawo
        node->left = (child != nullptr) ? child->right : nullptr;

        if (node->left != nullptr)
            node->left->parent = node;

        if (child != nullptr)
            child->right = node;
    }

    // Zaktualizuj rodzica dziecka na węzeł
    if (child != nullptr)
        node->parent = child;
}

// Napraw drzewo czerwono-czarne po wstawieniu
template <typename Key>
void RedBlackTree<Key>::ReArrange(RBNode<Key>* node) {
    while (node != nullptr && node->parent != nullptr && node->parent->color == Color::RED) {
        if (node->parent == node->parent->parent->left) {
            // Węzeł jest lewym dzieckiem swojego rodzica
            RBNode<Key>* siblingNode = node->parent->parent->right; // Znajdź brata (uncle) węzła
            if (siblingNode != nullptr && siblingNode->color == Color::RED) {
                // Przypadek 1: Wujek (siblingNode) jest czerwony
                node->parent->color = Color::BLACK;
                siblingNode->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                node = node->parent->parent; // Przejście do dziadka (grandparent) i ponowna analiza
            }
            else {
                // Przypadek 2: Wujek (siblingNode) jest czarny lub null
                if (node == node->parent->right) {
                    // Podprzypadek 2a: Węzeł jest prawym dzieckiem swojego rodzica
                    node = node->parent;
                    Rotate(node, Direction::LEFT); // Rotacja w lewo, aby uzyskać podprzypadek 2b
                }

                // Podprzypadek 2b: Węzeł jest lewym dzieckiem swojego rodzica
                node->parent->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                Rotate(node->parent->parent, Direction::RIGHT); // Rotacja w prawo, aby zrównoważyć drzewo
            }
        }
        else {
            // Przypadek symetryczny dla lewej i prawej strony
            RBNode<Key>* siblingNode = node->parent->parent->left; // Znajdź brata (uncle) węzła
            if (siblingNode != nullptr && siblingNode->color == Color::RED) {
                // Przypadek 1: Wujek (siblingNode) jest czerwony
                node->parent->color = Color::BLACK;
                siblingNode->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                node = node->parent->parent; // Przejście do dziadka (grandparent) i ponowna analiza
            }
            else {
                // Przypadek 2: Wujek (siblingNode) jest czarny lub null
                if (node == node->parent->left) {
                    // Podprzypadek 2a: Węzeł jest lewym dzieckiem swojego rodzica
                    node = node->parent;
                    Rotate(node, Direction::RIGHT); // Rotacja w prawo, aby uzyskać podprzypadek 2b
                }

                // Podprzypadek 2b: Węzeł jest prawym dzieckiem swojego rodzica
                node->parent->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                Rotate(node->parent->parent, Direction::LEFT); // Rotacja w lewo, aby zrównoważyć drzewo
            }
        }
    }

    // Upewnij się, że korzeń jest czarny
    root->color = Color::BLACK;
}

