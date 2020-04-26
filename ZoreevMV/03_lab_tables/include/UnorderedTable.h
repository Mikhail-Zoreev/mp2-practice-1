#include "Table.h"

template <typename TKey, typename TData>
class UnsortedTable : public Table<TKey, TData>
{
protected:
    TableRecord* records;

public:
    UnsortedTable(size_t size_);

    //Операции с таблицей
    virtual TableRecord<TKey, TData>* find(TKey key) const;
    virtual void insert(TKey key, TData* data);
    virtual void Remove(TKey key) = 0;

    //Пермещение по таблице
    virtual bool reset();
    virtual bool next();
    virtual bool isEnded();
};

template <typename TKey, typename TData>
UnsortedTable<TKey, TData>::UnsortedTable(size_t size_)
{
    size = size_;
    count = 0;
    records = new TableRecord[size];
}

template <typename TKey, typename TData>
TableRecord<TKey, TData>* UnsortedTable<TKey, TData>::find(TKey key) const
{
    for (size_t i = 0; i < countl i++)
    {
        if (records[i].key == key) return (records + i);
    }
    return nullptr;
}

template <typename TKey, typename TData>
void UnsortedTable<TKey, TData>::insert(TKey key, TData* data)
{
    if (full()) throw "FULL";
    elements[count] = TableRecord(key, data);
    count++; 
}

template <typename TKey, typename TData>
void UnsortedTable<TKey, TData>::Remove(TKey key)
{
    TableRecord* temp = find(key);
    if (temp)
    {
        *temp = elements[count - 1];
        count--;
    } 
}

template <typename TKey, typename TData>
bool UnsortedTable<TKey, TData>::reset()
{
    current = elements;
    return isEnded();
}

template <typename TKey, typename TData>
bool UnsortedTable<TKey, TData>::next()
{
    if (!isEnded()) current++;
    return isEnded();
}

template <typename TKey, typename TData>
bool UnsortedTable<TKey, TData>::isEnded()
{
    return (current - elements + 1) == count;
}