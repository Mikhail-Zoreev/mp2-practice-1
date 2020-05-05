#include "Table.h"

template <typename TKey, typename TData>
class UnorderedTable : public Table<TKey, TData>
{
protected:
    TableRecord<TKey, TData>** records;
    size_t current;

public:
    UnorderedTable(size_t size_ = 10);
    UnorderedTable(const UnorderedTable<TKey, TData>& temp);
    ~UnorderedTable();

    //Операции с таблицей
    virtual TableRecord<TKey, TData>* find(TKey key_) const;
    virtual void insert(TKey key_, const TData* data_);
    virtual void insert(TKey key_, const TData& data_);
    virtual void remove(TKey key_);

    //Пермещение по таблице
    virtual bool reset();
    virtual bool next();
    virtual bool isEnded() const;

    //Доступ к текущей записи
    virtual TKey getKey();
    virtual TData* getData();

};

template <typename TKey, typename TData>
UnorderedTable<TKey, TData>::UnorderedTable(size_t size_)
{
    this->size = size_;
    this->count = 0;
    current = 0;
    records = new TableRecord<TKey, TData>*[this->size];
}

template <typename TKey, typename TData>
UnorderedTable<TKey, TData>::UnorderedTable(const UnorderedTable<TKey, TData>& temp)
{
    this->size = temp.size_;
    this->count = temp.count;
    current = 0;
    records = new TableRecord*[this->size];
    for (size_t i = 0; i < this->count; i++)
    {
        records[i] = new TableRecord(*(temp.records[i]));
    }
}

template <typename TKey, typename TData>
UnorderedTable<TKey, TData>::~UnorderedTable()
{
    this->size = 0;
    this->count = 0;
    current = 0;
    for (size_t i = 0; i < this->count; i++)
    {
        delete records[i];
    }
    if (records != nullptr) delete[] records;
}

template <typename TKey, typename TData>
TableRecord<TKey, TData>* UnorderedTable<TKey, TData>::find(TKey key_) const
{
    for (size_t i = 0; i < this->count; i++)
    {
        if (records[i]->key == key) return records[i];
    }
    return nullptr;
}

template <typename TKey, typename TData>
void UnorderedTable<TKey, TData>::insert(TKey key, const TData* data_)
{
    if (this->full()) throw "FULL";
    records[this->count] =  new TableRecord<TKey, TData>(key, data);
    this->count++; 
}

template <typename TKey, typename TData>
void UnorderedTable<TKey, TData>::insert(TKey key_, const TData& data_)
{
    insert(key, &data);
}

template <typename TKey, typename TData>
void UnorderedTable<TKey, TData>::remove(TKey key_)
{
    TableRecord<TKey, TData>* temp = find(key);
    if (temp)
    {
        *temp = *records[this->count - 1];
        delete records[this->count - 1];
        records[this->count - 1] = nullptr;
        this->count--;
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
bool UnorderedTable<TKey, TData>::isEnded() const
{
    return (current + 1) == this->count;
}

template <typename TKey, typename TData>
TKey UnorderedTable<TKey, TData>::getKey()
{
    return records[current]->key;
}

template <typename TKey, typename TData>
TData* UnorderedTable<TKey, TData>::getData()
{
    return records[current]->data;
}