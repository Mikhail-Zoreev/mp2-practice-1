#include <iostream>
#include "../include/SearchTreeTable.h"

int main(int argc, char* argv[])
{
    SearchTreeTable<size_t, size_t> table;
    table.insert(2, 1);
    table.insert(1, 1);
    table.insert(3, 1);
    table.insert(6, 1);
    table.insert(4, 1);
    table.insert(7, 1);
    table.insert(5, 1);
    table.reset();
    while (!table.isEnded())
    {
        std::cout << table.getKey();
        table.next();
    }
    std::cout << table.getKey() << std::endl;

    SearchTreeTable<size_t, size_t> copy(table);

    copy.reset();
    while (!copy.isEnded())
    {
        std::cout << copy.getKey();
        copy.next();
    }
    std::cout << copy.getKey();
}