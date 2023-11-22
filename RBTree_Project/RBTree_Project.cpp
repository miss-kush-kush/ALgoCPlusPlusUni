#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <numeric>
#include <algorithm>
#include "RBTree.cpp"




void test()
{
    std::vector<int> v(8);
    std::iota(v.begin(), v.end(), 0);
    std::map<int, int> heights, root_data;
    do
    {
        RedBlackTree<int> t;
        for (int i : v)
            t.insert(i);
        ++heights[t.getHeight()];
        ++root_data[t.get_root_data()];

    } while (std::next_permutation(v.begin(), v.end()));
    for (auto [height, cnt] : heights)
        std::cout << height << ": " << cnt << std::endl;
    std::cout << "***" << std::endl;
    for (auto [data, cnt] : root_data)
        std::cout << data << ": " << cnt << std::endl;
}

int main() {

    test();
    RBNode<int>* node;
    const int MAX_ORDER = 7; // maksymalny rzad wielkosci dodawanych danych
    RedBlackTree<int>* rbt = new RedBlackTree<int>(); // stworzenie drzewa
    for (int o = 1; o <= MAX_ORDER; o++)
    {
        const int n = pow(10, o); // rozmiar danych
        // dodawanie do drzewa
        clock_t t1 = clock();
        for (int i = 0; i < n; i++)
        {
            int data = rand() % n; // Generate random data (int)
            rbt->insert(data); // dodanie ( drugi argument to wskaznik na komparator )
        }
        clock_t t2 = clock();
        // Output tree and timing measurements
        double timeToAdd = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
        std::cout << "Time to add " << n << " elements: " << timeToAdd << " seconds" << std::endl;

        const int m = pow(10, 4); // Number of search attempts
        int hits = 0; // Number of hits
        t1 = clock();
        for (int i = 0; i < m; i++) {
            int data = rand() % n; // Generate random data for search
            node = rbt->search(data);
            if (node) {
                int result = node->key;
                if (result != 0) {
                    hits++;
                }
            }

        }
        t2 = clock();
        // Output timing measurements and number of hits
        double timeToSearch = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
        std::cout << "Time to search " << m << " elements: " << timeToSearch << " seconds" << std::endl;
    }
    delete rbt;
    return 0;
}
