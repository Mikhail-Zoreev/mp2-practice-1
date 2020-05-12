#include <iostream>
#include <string>

#include "../include/SearchTreeTable.h"
#include "../include/UnorderedTable.h"
#include "../include/SortedTable.h"
#include "../include/HashTable.h"


int main(int argc, char* argv[])
{
    Table<size_t, std::string>* table;
    char mode;

    std::cout << "Please, input table type" << std::endl;
    std::cout << "0    Search tree table" << std::endl;
    std::cout << "1    Unordered table" << std::endl;
    std::cout << "2    Sorted table" << std::endl;
    std::cout << "3    Hash Table" << std::endl;
    std::cin >> mode;

    switch (mode)
    {
    case '0':
        table = new SearchTreeTable<size_t, std::string>;
        break;

    case '1':
        table = new UnorderedTable<size_t, std::string>(5);
        break;
    case '2':
        table = new SortedTable<size_t, std::string>(5);
        break;
    case '3':
        table = new HashTable<size_t, std::string>(5);
        break;
    default:
        std::cout << "Wrong type" << std::endl;
        return 1;
    }

    //--------Тест вставки--------------------------------------------------------------------------

    std::cout << std::endl << "1) Insertation test" << std::endl;

    table->insert(13, "John");
    table->insert(9, "Karl");
    table->insert(2, "Ann");
    table->insert(7, "Harry");
    table->insert(16, "Walter");

    table->reset();
    for (size_t i = 0; i < table->getCount(); i++)
    {
        std::cout << table->getKey() << " " << *(table->getData()) << std::endl;
        table->next();
    }

    //--------Тест проверки на конец таблицы--------------------------------------------------------

    std::cout << std::endl << "2) Table end check test" << std::endl;

    if (table->isEnded())
    {
        std::cout << "Table is ended" << std::endl;
    }
    else
    {
        std::cout << "Table is not ended" << std::endl;
    }

    std::cout << std::endl << "Reseting position" << std::endl;
    table->reset();

    if (table->isEnded())
    {
        std::cout << "Table is ended" << std::endl;
    }
    else
    {
        std::cout << "Table is not ended" << std::endl;
    }

    //--------Тест проверки на полноту--------------------------------------------------------------

    std::cout << std::endl << "3) Table full check test" << std::endl;

    if (table->full())
    {
        std::cout << "Table is full, current count is " << table->getCount() << std::endl;
    }
    else
    {
        std::cout << "Table is not full, current count is " << table->getCount() << std::endl;
    }

    //--------Тест удаления элемента----------------------------------------------------------------

    std::cout << std::endl << "4) Recorod removal test" << std::endl;
    std::cout << "Removing records with keys 13, 2 and 16" << std::endl;

    table->remove(13);
    table->remove(2);
    table->remove(16);

    table->reset();
    for (size_t i = 0; i < table->getCount(); i++)
    {
        std::cout << table->getKey() << " " << *(table->getData()) << std::endl;
        table->next();
    }
}