#include <iostream>
#include "../include/HashTable.h"

int main(int argc, char* argv[])
{
    HashTable<size_t, size_t> test;
    test.insert(1, 1);
    test.insert(4, 2);
    test.remove(1);
    test.reset();
    std::cout << test.getKey();
    test.next();
    std::cout << test.getKey();
}