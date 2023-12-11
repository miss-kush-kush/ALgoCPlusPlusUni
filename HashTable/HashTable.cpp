#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>

const double FILL_LIMIT = 0.75; // Filling limit for resizing

// Hash Table Class
template <typename V>
class HashTable {
private:
    struct Entry {
        std::string key;
        V value;
        Entry(const std::string& k, const V& v) : key(k), value(v) {}
    };

    std::vector<std::vector<Entry>> table;
    int currentSize;
    int maxSize;

    int hash(const std::string& key) {
        int hashVal = 0;
        int q = key.length();
        for (int i = 0; i < q; ++i) {
            hashVal = (hashVal * 31 + key[i]) % maxSize;
        }
        return hashVal;
    }

    void rehash() {
        int newMaxSize = maxSize * 2;
        std::vector<std::vector<Entry>> newTable(newMaxSize);

        for (const auto& bucket : table) {
            for (const auto& entry : bucket) {
                int index = hash(entry.key);
                newTable[index].push_back(entry);
            }
        }

        table = std::move(newTable);
        maxSize = newMaxSize;
    }

public:
    HashTable() : currentSize(0), maxSize(16) {
        table.resize(maxSize);
    }

    ~HashTable() {
        clear();
    }

    void put(const std::string& key, const V& value) {
        int index = hash(key);
        for (auto& entry : table[index]) {
            if (entry.key == key) {
                entry.value = value; // Replace the value if the key already exists
                return;
            }
        }
        table[index].push_back(Entry(key, value));
        currentSize++;

        if (currentSize >= FILL_LIMIT * maxSize) {
            rehash();
        }
    }

    V* get(const std::string& key) {
        int index = hash(key);
        for (auto& entry : table[index]) {
            if (entry.key == key) {
                return &entry.value;
            }
        }
        return nullptr;
    }

    bool remove(const std::string& key) {
        int index = hash(key);
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key == key) {
                bucket.erase(it);
                currentSize--;
                return true;
            }
        }
        return false;
    }

    void clear() {
        for (auto& bucket : table) {
            bucket.clear();
        }
        currentSize = 0;
        maxSize = 16;
        table.resize(maxSize);
    }

    std::string toString() {
        std::string result = "hash table:\n";
        result += "current_size: " + std::to_string(currentSize) + "\n";
        result += "max_size: " + std::to_string(maxSize) + "\n";
        result += "table:\n{\n";
        for (size_t i = 0; i < table.size(); ++i) {
            if (!table[i].empty()) {
                result += std::to_string(i) + ": ";
                for (const auto& entry : table[i]) {
                    result += entry.key + " -> " + std::to_string(entry.value) + "; ";
                }
                result += "\n";
            }
        }
        result += "}\n";
        return result;
    }

    void printStats() {
        int minSize = std::numeric_limits<int>::max();
        int maxSize = 0;
        int nonNullLists = 0;
        double avgSize = 0.0;

        for (const auto& bucket : table) {
            if (!bucket.empty()) {
                int bucketSize = bucket.size();
                nonNullLists++;
                avgSize += bucketSize;
                minSize = std::min(minSize, bucketSize);
                maxSize = std::max(maxSize, bucketSize);
            }
        }

        if (nonNullLists > 0) {
            avgSize /= nonNullLists;
        }

        std::cout << "stats:\n";
        std::cout << "list min size: " << minSize << "\n";
        std::cout << "list max size: " << maxSize << "\n";
        std::cout << "non-null lists: " << nonNullLists << "\n";
        std::cout << "list avg size: " << avgSize << "\n";
    }
};

std::string randomKey(int length) {
    static const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string key;
    for (int i = 0; i < length; ++i) {
        key += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return key;
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    const int MAX_ORDER = 7; // Max order of data size
    HashTable<int>* ht = new HashTable<int>();

    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = static_cast<int>(pow(10, o)); // Data size

        // Adding to the hash table
        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            ht->put(randomKey(6), i); // Random 6-character keys with values as loop index
        }
        clock_t t2 = clock();

        // Printing the current state of the hash table and timing measurements
        std::cout << ht->toString();
        std::cout << "Time to add " << n << " elements: " << (double)(t2 - t1) / CLOCKS_PER_SEC << " seconds\n";

        // Searching in the hash table
        const int m = static_cast<int>(pow(10, 4));
        int hits = 0;
        t1 = clock();
        for (int i = 0; i < m; i++) {
            int* entry = ht->get(randomKey(6)); // Searching with a random key
            if (entry != nullptr) {
                hits++;
            }
        }
        t2 = clock();
        std::cout << "Time to search for " << m << " elements: " << (double)(t2 - t1) / CLOCKS_PER_SEC << " seconds " << hits<<" hits\n";

        // Printing statistics (length of lists inside the hash table)
        ht->printStats();

        // Clearing the hash table
        ht->clear();
    }

    delete ht;
    return 0;
}
