#include <iostream>
#include <list>
#include <cmath>
#include <random>
#include <chrono>

// funkcija za izračunavanje univerzalne hash vrijednosti za danu decimalnu vrijednost
int hash_function(int x) {
    int n = std::to_string(x).length();
    int a[n];

    // generiranje slučajnih brojeva ai
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(0,6);
    for(int i = 0; i < n; i++) {
        a[i] = distribution(generator);
    }

    // izračunavanje hash vrijednosti f(x)
    int fx = 0;
    for(int i = 0; i < n; i++) {
        fx += a[i]*std::pow(7,i);
    }
    fx = fx % 7;
    return fx;
}

// struktura podataka koja koristi univerzalnu hash funkciju
struct HashTable {
    std::list<std::pair<int,float>>* table;
    int size;

    // konstruktor
    HashTable(int size) {
        this->size = size;
        table = new std::list<std::pair<int,float>>[size];
    }

    // destruktor
    ~HashTable() {
        delete[] table;
    }

    // umetanje vrijednosti u tablicu
    void insert(int key, float value) {
        int index = hash_function(key);
        table[index].push_back(std::make_pair(key,value));
    }

    // pretraživanje vrijednosti u tablici
    float search(int key) {
        int index = hash_function(key);
        for(auto i = table[index].begin(); i != table[index].end(); i++) {
            if(i->first == key) {
                return i->second;
            }
        }
        return -1;
    }
};

int main() {
    HashTable ht(7);

    // testiranje umetanja vrijednosti
    ht.insert(123456, 3.14);
    ht.insert(3456, 2.71);
    ht.insert(2345, 1.23);

    // testiranje pretraživanja vrijednosti
    std::cout << ht.search(123456) << std::endl;
    std::cout << ht.search(3456) << std::endl;
    std::cout << ht.search(2345) << std::endl;
    std::cout << ht.search(999999) << std::endl;

    return 0;
}
