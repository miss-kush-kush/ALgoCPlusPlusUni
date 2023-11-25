#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <numeric>
#include <algorithm>
#include "RBTree.h"

void test()
{
    vector<int> v(8);
    iota(v.begin(), v.end(), 0);
    map<int, int> heights, root_data;
    do
    {
        RedBlackTree<int> t;
        for (int i : v)
            t.insert(i);
        ++heights[t.height()];
        ++root_data[t.get_root_data()];

    } while (next_permutation(v.begin(), v.end()));
    for (auto [height, cnt] : heights)
        cout << height << ": " << cnt << endl;
    cout << "***" << endl;
    for (auto [data, cnt] : root_data)
        cout << data << ": " << cnt << endl;
}

int main() {

    test();
    RBNode<int>* node;
    const int MAX_ORDER = 7; // maksymalny rzad wielkosci dodawanych danych
    RedBlackTree<int>* rbt = new RedBlackTree<int>(); // stworzenie drzewa
    int inputData[] = { 55, 69, 62, 57, 35, 83, 72 ,74 };

    for (int i = 0; i < 8; i++) {
        rbt->insert(inputData[i]);
    }
    rbt->Display(TraversalOrder::PREORDER);
    rbt->clear();
    for (int o = 1; o <= MAX_ORDER; o++)
    {
        const int n = pow(10, o); // rozmiar danych
        // dodawanie do drzewa
        clock_t t1 = clock();
        for (int i = 0; i < n; i++)
        {
            int data = rand() % abs(n); // Generowanie losowych danych (int)
            rbt->insert(data); // Dodanie (drugi argument to wskaźnik na komparator)
        }
        clock_t t2 = clock();
        // Wyświetlanie drzewa i pomiar czasu
        double timeToAdd = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
        cout << "Czas dodawania " << n << " elementów: " << timeToAdd << " sekund" << endl;

        const int m = pow(10, 4); // Liczba prób wyszukiwania
        int hits = 0; // Liczba trafień
        t1 = clock();
        for (int i = 0; i < m; i++) {
            int data = rand() % n; // Generowanie losowych danych do wyszukiwania
            node = rbt->search(data);
            if (node) {
                int result = node->key;
                if (result != 0) {
                    hits++;
                }
            }

        }
        t2 = clock();
        // Wyświetlanie pomiarów czasu i liczby trafień
        double timeToSearch = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
        cout << "Czas wyszukiwania " << m << " elementów: " << timeToSearch << " sekund" << endl;
        cout << "Height" << rbt->height() << endl;
    }

    delete rbt;
    return 0;
}
