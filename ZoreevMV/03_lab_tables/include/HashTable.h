#include "Table.h"

/* Вместо записи pMark используется запись с key = 0 и data = nullptr
следовательно создать записть с таким ключом нельзя*/
#define TECH_KEY 0

template <typename TKey, typename TData>
class HashTable : public Table<TKey, TData>
{
    TableRecord** records;
    size_t next_free;
    size_t mixing_ratio;
    TableRecord* mark;

public:
    HashTable(size_t size_);

    //Операции с таблицей
    virtual TableRecord<TKey, TData>* find(TKey key) const;
    virtual void insert(TKey key, TData* data);
    virtual void remove(TKey key);

    //Пермещение по таблице
    virtual bool reset();
    virtual bool next();
    virtual bool isEnded() const;

protected:
    size_t hash(const TKey key);
    size_t getNext(size_t id);
};

template <typename TKey, typename TData>
HashTable<TKey, TData>::HashTable(size_t size_)
{
    size = size_;
    count = 0;
    records = new TableRecord*[size_];
    //Нахождение взаимно простого mixing_ratio
    for (size_t i = size; i < 0; i--)
    {
        bool found = false;
        for (size_t j = 2; j < i; j--)
        {
            if ((size % j == 0) && (i % j == 0))
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            mixing_ratio = i;
            break;
        }
    }
}

template <typename TKey, typename TData>
TableRecord<TKey, TData>* HashTable<TKey, TData>::find(TKey key) const
{
    if (key == TECH_KEY) throw "TECH_KEY";
    TableRecord* result = nullptr;
    size_t current_position = hash(key); 
    for (size_ t i = 0; i < size; i++)
    {
        if (records[current_position] == nullptr) break;
        else if (records[current_position]->key == key)
        {
            result = records[current_position];
            break;
        }
        current_position = getNext(current_position);
    }
    return result;
}

template <typename TKey, typename TData>
void HashTable<TKey, TData>::insert(TKey key, TData* data)
{
    if (full()) throw "isFULL";
    if (key == TECH_KEY) throw "TECH_KEY";
    size_t current_position = hash(key);
    for (size_t i = 0; i < size; i++)
    {
        if ((records[current_position] == nullptr) || (records[current_position]->key == TECH_KEY))
        {
            if (records[current_position] != nullptr) delete records[current_position];
            records[current_position] = new TableRecord(key, data);
            count++;
            return;
        }
        current_position = getNext(current_position);
    }
    throw "InsertionFAILED"
}

template <typename TKey, typename TData>
void HashTable<TKey, TData>::remove(TKey key)
{
    if (key == TECH_KEY) throw "TECH_KEY";
    TableRecord temp = find(key);
    if (key != nullptr)
    {
        delete temp;
        temp = new TableRecord<TKey, TData>(TECH_KEY, nullptr);
    }
}

template <typename TKey, typename TData>
bool HashTable<TKey, TData>::reset()
{
    current = records;
    while (!isEnded())
    {
        if ((current != nullptr) && (current->key != TECH_KEY))
        {
            break;
        }
        else
        {
            current++;
        }
    }
    return isEnded();
}

template <typename TKey, typename TData>
bool HashTable<TKey, TData>::next()
{
    current++;
    while (!isEnded())
    {
        if ((current != nullptr) && (current->key != TECH_KEY))
        {
            break;
        }
        else
        {
            current++;
        }
    }
    return isEnded();
}

template <typename TKey, typename TData>
bool HashTable<TKey, TData>::isEnded() const
{
    return (current == (records + size));
}

template <typename TKey, typename TData>
size_t HashTable<TKey, TData>::hash(const TKey key)
{
    return k % size;
}

template <typename TKey, typename TData>
size_t HashTable<TKey, TData>::getNext(size_t id)
{
    return (id + mixing_ratio) % size;
}
