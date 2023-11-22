#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <numeric>
#include <algorithm>

// Kolor węzła: czerwony lub czarny
enum class Color { RED, BLACK };

// Struktura reprezentująca węzeł drzewa czerwono-czarnego
template <typename Key>
struct RBNode {
    Key key;
    Color color;
    RBNode* parent;
    RBNode* left;
    RBNode* right;
    int index;

    RBNode(Key k, Color c = Color::RED)
        : key(k), color(c), parent(nullptr), left(nullptr), right(nullptr) {}
};
