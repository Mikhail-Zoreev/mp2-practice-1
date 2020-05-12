#include <iostream>
#include <string>

#include "SearchTreeTable.h"
#include "UnorderedTable.h"
#include "SortedTable.h"
#include "HashTable.h"

#include "Exception.h"

int main(int argc, char* argv[])
{
    Table<size_t, std::string>* table;
    char mode;
    bool closed = false;
    size_t key;
    std::string data;

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

    std::cout << "Please, input command" << std::endl;
    std::cout << "0    Insert record" << std::endl;
    std::cout << "1    Remove record" << std::endl;
    std::cout << "2    Check if is ended" << std::endl;
    std::cout << "3    Move next" << std::endl;
    std::cout << "4    Reset position" << std::endl;
    std::cout << "5    Get current data" << std::endl;
    std::cout << "6    Check if empty" << std::endl;
    std::cout << "7    Check if full" << std::endl;
    std::cout << "8    Get count" << std::endl;
    std::cout << "q    Search tree table" << std::endl;

    while (!closed)
    {
        try
        {
            std::cin >> mode;
            switch (mode)
            {
            case '0':    
                std::cout << "Please, input key ";
                std::cin >> key;
                std::cout << "Please, input data ";
                std::cin >> data;
                table->insert(key, data);

                std::cout << "Result:" << std::endl;
                table->reset();
                for (size_t i = 0; i < table->getCount(); i++)
                {
                    std::cout << table->getKey() << " " << *(table->getData()) << std::endl;
                    table->next();
                }
                break;

            case '1':
                std::cout << "Please, input key ";
                std::cin >> key;
                table->remove(key);

                std::cout << "Result:" << std::endl;
                table->reset();
                for (size_t i = 0; i < table->getCount(); i++)
                {
                    std::cout << table->getKey() << " " << *(table->getData()) << std::endl;
                    table->next();
                }
                break;

            case '2':
                if (table->isEnded())
                {
                    std::cout << "Table is ended" << std::endl;
                }
                else
                {
                    std::cout << "Table is not ended" << std::endl;
                }
                break;

            case '3':
                table->next();

                break;
            case '4':
                table->reset();

                break;
            case '5':
                std::cout << "Data: " << *(table->getData()) << std::endl;

                break;

            case '6':
                if (table->empty())
                {
                    std::cout << "Table is empty" << std::endl;
                }
                else
                {
                    std::cout << "Table is not empty" << std::endl;
                }

                break;

            case '7':
                if (table->full())
                {
                    std::cout << "Table is full" << std::endl;
                }
                else
                {
                    std::cout << "Table is not full" << std::endl;
                }

                break;

            case '8':
                std::cout << "Count: " << table->getCount() << std::endl;

                break;
            case 'q':
                closed = true;

                break;
            }
        }
        catch (IsFullException)
        {
            std::cout << "Can't insert, table is full" << std::endl;
        }
        catch (BadDataException)
        {
            std::cout << "Bad input" << std::endl;
        }
        catch (IterationChainBrokenException)
        {
            std::cout << "Iteration chain broken, you should to reset" << std::endl;
        }
    }
}