#pragma once

#include "Table.h"

/* Вместо записи pMark с data = nullptr
следовательно создать записть с пустым data нельзя*/

template <typename TKey, typename TData>
class HashTable : public Table<TKey, TData>
{
    TableRecord<TKey, TData>** records;
    size_t current;
    size_t mixing_ratio;

public:
    HashTable(size_t size_ = 10);

    //Операции с таблицей
    virtual TableRecord<TKey, TData>* find(TKey key) const;
    virtual void insert(TKey key, const TData* data);
    virtual void insert(TKey key, const TData& data);
    virtual void remove(TKey key);

    //Пермещение по таблице
    virtual bool reset();
    virtual bool next();
    virtual bool isEnded() const;

    //Доступ к текущей записи
    virtual TKey getKey();
    virtual TData* getData();

protected:
    size_t hash(const TKey key) const;
    size_t getNext(size_t id) const;
};

template <typename TKey, typename TData>
HashTable<TKey, TData>::HashTable(size_t size_)
{
    this->size = size_;
    this->count = 0;
    current = 0;
    records = new TableRecord<TKey, TData>*[size_];
    for (size_t i = 0; i < this->size; i++)
    {
        records[i] = nullptr;
    }
    //Нахождение взаимно простого mixing_ratio
    for (size_t i = this->size; i < 0; i--)
    {
        bool found = false;
        for (size_t j = 2; j < i; j++)
        {
            if ((this->size % j == 0) && (i % j == 0))
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
    TableRecord<TKey, TData>* result = nullptr;
    size_t current_position = hash(key); 
    for (size_t i = 0; i < this->size; i++)
    {
        if (records[current_position] == nullptr) break;
        else if ((records[current_position]->key == key) && (records[current_position] != nullptr))
        {
            result = records[current_position];
            break;
        }
        current_position = getNext(current_position);
    }
    return result;
}

template <typename TKey, typename TData>
void HashTable<TKey, TData>::insert(TKey key, const TData* data)
{
    if (this->full()) throw "isFULL";
    if (data == nullptr) throw "EmptyDATA";
    size_t current_position = hash(key);
    for (size_t i = 0; i < this->size; i++)
    {
        if ((records[current_position] == nullptr) || (records[current_position]->data == nullptr))
        {
            if (records[current_position] != nullptr) delete records[current_position];
            records[current_position] = new TableRecord<TKey, TData>(key, data);
            this->count++;
            return;
        }
        current_position = getNext(current_position);
    }
    throw "InsertionFAILED";
}

template <typename TKey, typename TData>
void HashTable<TKey, TData>::insert(TKey key, const TData& data)
{
    insert(key, &data);
}

template <typename TKey, typename TData>
void HashTable<TKey, TData>::remove(TKey key)
{
    TableRecord<TKey, TData>* temp = find(key);
    if (temp != nullptr)
    {
        delete temp->data;
        temp->data = nullptr;
        temp->key = 0;
    }
}

template <typename TKey, typename TData>
bool HashTable<TKey, TData>::reset()
{
    current = 0;
    while (!isEnded())
    {
        if ((records[current] != nullptr) && (records[current]->data != nullptr))
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
    if (isEnded()) return true;
    current++;
    while (!isEnded())
    {
        if ((records[current] != nullptr) && (records[current]->data != nullptr))
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
    for (size_t i = current + 1; i < this->size; i++)
    {
        if (records[i] != nullptr && records[i]->data != nullptr) return false;
    }
    return true;
}

template <typename TKey, typename TData>
TKey HashTable<TKey, TData>::getKey()
{
    return records[current]->key;
}

template <typename TKey, typename TData>
TData* HashTable<TKey, TData>::getData()
{
    return records[current]->data;
}

template <typename TKey, typename TData>
size_t HashTable<TKey, TData>::hash(const TKey key) const
{
    return key % this->size;
}

template <typename TKey, typename TData>
size_t HashTable<TKey, TData>::getNext(size_t id) const
{
    return (id + mixing_ratio) % this->size;
}
