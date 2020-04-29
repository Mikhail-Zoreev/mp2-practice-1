#include "Table.h"

template <typename TKey, typename TData>
class UnorderedTable : public Table<TKey, TData>
{
protected:
    TableRecord* records;

public:
    UnorderedTable(size_t size_);
    UnorderedTable(const UnorderedTable<TKey, TData>& temp);
    ~UnorderedTable();

    //Операции с таблицей
    virtual TableRecord<TKey, TData>* find(TKey key) const;
    virtual void insert(TKey key, TData* data);
    virtual void remove(TKey key);

    //Пермещение по таблице
    virtual bool reset();
    virtual bool next();
    virtual bool isEnded();
};

template <typename TKey, typename TData>
UnorderedTable<TKey, TData>::UnorderedTable(size_t size_)
{
    size = size_;
    count = 0;
    records = new TableRecord[size];
}

template <typename TKey, typename TData>
UnorderedTable<TKey, TData>::UnorderedTable(const UnorderedTable<TKey, TData>& temp)
{
    size = temp.size_;
    count = temp.count;
    records = new TableRecord[size];
    for (size_t i = 0; i < count; i++)
    {
        records[i] = temp.records[i];
    }
}

template <typename TKey, typename TData>
UnorderedTable<TKey, TData>::~UnorderedTable()
{
    size = 0;
    count = 0;
    if (records != nullptr) delete[] records;
}

template <typename TKey, typename TData>
TableRecord<TKey, TData>* UnorderedTable<TKey, TData>::find(TKey key) const
{
    for (size_t i = 0; i < countl i++)
    {
        if (records[i].key == key) return (records + i);
    }
    return nullptr;
}

template <typename TKey, typename TData>
void UnorderedTable<TKey, TData>::insert(TKey key, TData* data)
{
    if (full()) throw "FULL";
    elements[count] = TableRecord(key, data);
    count++; 
}

template <typename TKey, typename TData>
void UnorderedTable<TKey, TData>::remove(TKey key)
{
    TableRecord* temp = find(key);
    if (temp)
    {
        *temp = elements[count - 1];
        count--;
    } 
}

template <typename TKey, typename TData>
bool UnorderedTable<TKey, TData>::reset()
{
    current = elements;
    return isEnded();
}

template <typename TKey, typename TData>
bool UnorderedTable<TKey, TData>::next()
{
    if (!isEnded()) current++;
    return isEnded();
}

template <typename TKey, typename TData>
bool UnorderedTable<TKey, TData>::isEnded()
{
    return (current - elements + 1) == count;
}