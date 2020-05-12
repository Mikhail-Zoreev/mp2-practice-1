#pragma once

#include "UnorderedTable.h"

#include "Exception.h"

template <typename TKey, typename TData>
class SortedTable : public UnorderedTable<TKey, TData>
{
public:
    SortedTable(size_t size_ = 10);
    SortedTable(const SortedTable<TKey, TData>& temp);

    //Операции с таблицей
    virtual TableRecord<TKey, TData>* find(TKey key_) const;
    virtual void insert(TKey key_, const TData* data_);
    virtual void insert(TKey key_, const TData& data_);
    virtual void remove(TKey key_);

protected:
    void sort();
};

template <typename TKey, typename TData>
SortedTable<TKey, TData>::SortedTable(size_t size_) : UnorderedTable<TKey, TData>(size_)
{

}

template <typename TKey, typename TData>
SortedTable<TKey, TData>::SortedTable(const SortedTable<TKey, TData>& temp) : UnorderedTable(temp)
{
    sort();
}

template <typename TKey, typename TData>
TableRecord<TKey, TData>* SortedTable<TKey, TData>::find(TKey key_) const
{
    size_t left = 0, right = this->count;
    while(left != right)
    {
        size_t middle = (left + right) / 2;
        if (this->records[middle]->key == key_)
        {
            return this->records[middle];
        }
        else if (this->records[middle]->key < key_)
        {
            left = middle;
        }
        else
        {
            right = middle;
        }
    }
    return nullptr;
}

template <typename TKey, typename TData>
void SortedTable<TKey, TData>::insert(TKey key_, const TData* data_)
{
    if (this->full()) throw IsFullException();

    size_t index = 0;
    while ((index < this->count) && (this->records[index]->key < key_))
    {
        index++;
    }
    TableRecord<TKey, TData> *first = nullptr, *second = this->records[index];
    for (size_t i = index + 1; i <= this->count; i++)
    {
        first = second;
        second = this->records[i];
        this->records[i] = first;
    }

    this->records[index] = new TableRecord<TKey, TData>(key_, data_);
    this->count++;
}

template <typename TKey, typename TData>
void SortedTable<TKey, TData>::insert(TKey key_, const TData& data_)
{
    insert(key_, &data_);
}

template <typename TKey, typename TData>
void SortedTable<TKey, TData>::remove(TKey key_)
{
    TableRecord<TKey, TData>* temp = find(key_);
    if (temp)
    {
        *temp = *this->records[this->count - 1];
        delete this->records[this->count - 1];
        this->records[this->count - 1] = nullptr;
        this->count--;
        sort();
    }
}

template <typename TKey, typename TData>
void SortedTable<TKey, TData>::sort()
{
    if (this->count <= 1) return;

    for (size_t i = 0; i < this->count; i++)
    {
        size_t min = this->count - 1;
        for (size_t j = i; j < this->count; j++)
        {
            if (*(this->records[j]) < *(this->records[min])) min = j;
        }
        TableRecord<TKey, TData>* temp = this->records[i];
        this->records[i] = this->records[min];
        this->records[min] = temp;
    }
}