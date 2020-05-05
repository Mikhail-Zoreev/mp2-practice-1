#include "UnorderedTable.h"

template <typename TKey, typename TData>
class SortedTable : public UnorderedTable<TKey, TData>
{
public:
    SortedTable(size_t size_ = 10);
    SortedTable(const SortedTable<TKey, TData>& temp);

    //Операции с таблицей
    virtual TableRecord<TKey, TData>* find(TKey key_) const;
    virtual void insert(TKey key_, const TData* data_); //TODO: Сделать без сортировки
    virtual void insert(TKey key_, const TData& data_); //TODO: Сделать без сортировки
    virtual void remove(TKey key_);

protected:
    void sort();
};

template <typename TKey, typename TData>
SortedTable<TKey, TData>::SortedTable(size_t size_) : UnorderedTable<TKey, TData>(size_)
{
    sort();
}

template <typename TKey, typename TData>
SortedTable<TKey, TData>::SortedTable(const SortedTable<TKey, TData>& temp) : UnorderedTable(temp)
{
    
}

template <typename TKey, typename TData>
TableRecord<TKey, TData>* SortedTable<TKey, TData>::find(TKey key_) const
{
    size_t left = 0, right = this->count;
    while(left != right)
    {
        size_t middle = (left + right) / 2;
        if (this->records[middle]->key == key)
        {
            return this->records[middle];
        }
        else if (this->records[middle]->key < key)
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
    if (this->full()) throw "FULL";
    this->records[this->count] =  new TableRecord<TKey, TData>(key, data);
    this->count++;
    sort();
}

template <typename TKey, typename TData>
void SortedTable<TKey, TData>::insert(TKey key_, const TData& data_)
{
    insert(key, &data);
}

template <typename TKey, typename TData>
void SortedTable<TKey, TData>::remove(TKey key_)
{
    TableRecord<TKey, TData>* temp = find(key);
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