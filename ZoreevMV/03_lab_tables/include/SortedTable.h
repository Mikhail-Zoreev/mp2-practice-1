#include "UnorderedTable.h"

template <typename TKey, typename TData>
class SortedTable : public UnorderedTable<TKey, TData>
{
public:
    SortedTable(size_t size);
    SortedTable(const SortedTable<TKey, TData>& temp);

    //Операции с таблицей
    virtual TableRecord<TKey, TData>* find(TKey key) const;
    virtual void insert(TKey key, TData* data); //TODO: Сделать без сортировки
    virtual void remove(TKey key);              //TODO: Сделать без сортировки

private:
    void sort();
};

template <typename TKey, typename TData>
SortedTable<TKey, TData>::SortedTable(size_t size) : UnorderedTable<TKey, TData>(size_t size)
{
    sort();
}

template <typename TKey, typename TData>
SortedTable<TKey, TData>::SortedTable(const SortedTable<TKey, TData>& temp) : UnorderedTable(temp)
{
    
}

template <typename TKey, typename TData>
TableRecord<TKey, TData>* SortedTable<TKey, TData>::find(TKey key) const
{
    size_t left = 0, right = count;
    while(left != right)
    {
        size_t middle = (left + right) / 2;
        if (records[middle].key == key)
        {
            return (records + middle)
        }
        else if (record[middle].key < key)
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
void SortedTable<TKey, TData>::insert(TKey key, TData* data)
{
    if (full()) throw "FULL";
    elements[count] = TableRecord(key, data);
    count++;
    sort();
}

template <typename TKey, typename TData>
void SortedTable<TKey, TData>::remove(TKey key)
{
    TableRecord* temp = find(key);
    if (temp)
    {
        *temp = elements[count - 1];
        count--;
        sort();
    }
}

template <typename TKey, typename TData>
void SortedTable<TKey, TData>::sort()
{
    if (size <= 1) return;

    for (size_t i = 0; i < count; i++)
    {
        size_t min = count - 1;
        for (size_t j = i; j < count; j++)
        {
            if (records[j] < records[min]) min = j;
        }
        TableRecord<TKey, TData> temp(records[i]);
        records[i] = records[min];
        records[min] = temp;
    }
}