#include "Table.h"

template <typename TKey, typename TData>
class UnorderedTable : public Table<TKey, TData>
{
protected:
    TableRecord<TKey, TData>** records;
    size_t current;

public:
    UnorderedTable(size_t size_);
    UnorderedTable(const UnorderedTable<TKey, TData>& temp);
    ~UnorderedTable();

    //Операции с таблицей
    virtual TableRecord<TKey, TData>* find(TKey key) const;
    virtual void insert(TKey key, TData* data);
    virtual void insert(TKey key, const TData& data);
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
    current = 0;
    records = new TableRecord*[size];
}

template <typename TKey, typename TData>
UnorderedTable<TKey, TData>::UnorderedTable(const UnorderedTable<TKey, TData>& temp)
{
    size = temp.size_;
    count = temp.count;
    current = 0;
    records = new TableRecord*[size];
    for (size_t i = 0; i < count; i++)
    {
        records[i] = new TableRecord(*(temp.records[i]));
    }
}

template <typename TKey, typename TData>
UnorderedTable<TKey, TData>::~UnorderedTable()
{
    size = 0;
    count = 0;
    current = 0;
    for (size_t i = 0; i < count; i++)
    {
        delete records[i];
    }
    if (records != nullptr) delete[] records;
}

template <typename TKey, typename TData>
TableRecord<TKey, TData>* UnorderedTable<TKey, TData>::find(TKey key) const
{
    for (size_t i = 0; i < count; i++)
    {
        if (records[i]->key == key) return records[i];
    }
    return nullptr;
}

template <typename TKey, typename TData>
void UnorderedTable<TKey, TData>::insert(TKey key, TData* data)
{
    if (full()) throw "FULL";
    records[count] =  new TableRecord(key, data);
    count++; 
}

template <typename TKey, typename TData>
void UnorderedTable<TKey, TData>::insert(TKey key, const TData& data)
{
    insert(key, *data);
}

template <typename TKey, typename TData>
void UnorderedTable<TKey, TData>::remove(TKey key)
{
    TableRecord* temp = find(key);
    if (temp)
    {
        delete temp;
        if (count > 1)
        {
            temp = records[count - 1];
        }
            records[count - 1] = nullptr;
        count--;
    } 
}

template <typename TKey, typename TData>
bool UnorderedTable<TKey, TData>::reset()
{
    current = 0;
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
    return (current - 1) == count;
}