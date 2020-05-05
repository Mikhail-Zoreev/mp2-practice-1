#pragma once

template<typename TKey, typename TData>
struct TableRecord
{
    TKey key;
    TData* data;

    TableRecord(TKey key_, const TData* data_);
    TableRecord(TKey key_, const TData& data_);
    TableRecord(const TableRecord<TKey, TData>& temp);
    ~TableRecord();

    TableRecord<TKey, TData>& operator=(const TableRecord<TKey, TData> temp);

    bool operator<(const TableRecord<TKey, TData> temp);
    bool operator>(const TableRecord<TKey, TData> temp); 
    bool operator==(const TableRecord<TKey, TData> temp);
};


template<typename TKey, typename TData>
class Table
{
protected:
    size_t size;
    size_t count;

public:
    Table(size_t size_ = 10) {};

    //Операции с таблицей
    virtual TableRecord<TKey, TData>* find(TKey key_) const = 0;
    virtual void insert(TKey key, const TData* data) = 0;
    virtual void insert(TKey key, const TData& data) = 0;
    virtual void remove(TKey key) = 0;

    //Пермещение по таблице
    virtual bool reset() = 0;
    virtual bool next() = 0;
    virtual bool isEnded() const = 0;

    //Доступ к текущей записи
    virtual TKey getKey() = 0;
    virtual TData* getData() = 0;

    //Информационные методы
    bool empty() const;
    bool full() const;
    size_t getCount();
};


template<typename TKey, typename TData>
TableRecord<TKey, TData>::TableRecord(TKey key_, const TData* data_)
{
    key = key_;
    data = new TData(*data_);
}

template<typename TKey, typename TData>
TableRecord<TKey, TData>::TableRecord<TKey, TData>(TKey key_, const TData& data_)
{
    key = key_;
    data = new TData(data_);
}

template<typename TKey, typename TData>
TableRecord<TKey, TData>::TableRecord(const TableRecord<TKey, TData>& temp)
{
    key = temp.key;
    data = new TData(*temp.data);
}

template<typename TKey, typename TData>
TableRecord<TKey, TData>::~TableRecord()
{
    if (!data) delete data;
}

template<typename TKey, typename TData>
TableRecord<TKey, TData>& TableRecord<TKey, TData>::operator=(const TableRecord<TKey, TData> temp)
{
    key = temp.key;
    if (data != nullptr) delete data;
    data = new TData(*temp.data);
    return *this;
}

template<typename TKey, typename TData>
bool TableRecord<TKey, TData>::operator<(const TableRecord<TKey, TData> temp)
{
    return key < temp.key;
}

template<typename TKey, typename TData>
bool TableRecord<TKey, TData>::operator>(const TableRecord<TKey, TData> temp)
{
    return key > temp.key;
}

template<typename TKey, typename TData>
bool TableRecord<TKey, TData>::operator==(const TableRecord<TKey, TData> temp)
{
    return key == temp.key;
}

template<typename TKey, typename TData>
bool Table<TKey, TData>::empty() const
{
    return count == 0;
}

template<typename TKey, typename TData>
bool Table<TKey, TData>::full() const
{
    return count == size;
}

template<typename TKey, typename TData>
size_t Table<TKey, TData>::getCount()
{
    return count;
}