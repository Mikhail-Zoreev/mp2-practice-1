#include "Table.h"
#include "SearchTree.h"
#include "Exception.h"

template <typename TKey, typename TData>
class SearchTreeTable : public Table<TKey, TData>
{
    SearchTree<TKey, TableRecord<TKey, TData>>* root;
    TableRecord<TKey, TData>* current;
public:
    SearchTreeTable();
    SearchTreeTable(const SearchTreeTable& temp);
    ~SearchTreeTable();

    //Операции с таблицей
    virtual TableRecord<TKey, TData>* find(TKey key_) const;
    virtual void insert(TKey key_, const TData* data);
    virtual void insert(TKey key_, const TData& data_);
    virtual void remove(TKey key_);

    //Пермещение по таблице
    virtual bool reset();
    virtual bool next();
    virtual bool isEnded() const;

    //Доступ к текущей записи
    virtual TKey getKey();
    virtual TData* getData();

    //Информационные методы
    virtual bool full() const;
};

template <typename TKey, typename TData>
SearchTreeTable<TKey, TData>::SearchTreeTable()
{
    root = new SearchTree<TKey, TableRecord<TKey, TData>>();
    current = nullptr;
    this->count = 0;
}

template <typename TKey, typename TData>
SearchTreeTable<TKey, TData>::SearchTreeTable(const SearchTreeTable& temp)
{
    root = new SearchTree<TKey, TableRecord<TKey, TData>>(*(temp.root));
    this->count = temp.count;
    reset();
}

template <typename TKey, typename TData>
SearchTreeTable<TKey, TData>::~SearchTreeTable()
{
    delete root;
}

template <typename TKey, typename TData>
TableRecord<TKey, TData>* SearchTreeTable<TKey, TData>::find(TKey key_) const
{
    return (root->find(key_))->data;
}

template <typename TKey, typename TData>
void SearchTreeTable<TKey, TData>::insert(TKey key_, const TData* data_)
{
    root->insert(key_, new TableRecord<TKey, TData>(key_, data_));
    this->count++;
}

template <typename TKey, typename TData>
void SearchTreeTable<TKey, TData>::insert(TKey key_, const TData& data_)
{
    root->insert(key_, new TableRecord<TKey, TData>(key_, data_));
    this->count++;
}

template <typename TKey, typename TData>
void SearchTreeTable<TKey, TData>::remove(TKey key_)
{
    if (root->find(key_) != nullptr)
    {
        root->remove(key_);
        this->count--;
    }
}

template <typename TKey, typename TData>
bool SearchTreeTable<TKey, TData>::reset()
{
    current = nullptr;
    if (this->count != 0)
    {
        current = (root->findMin(root->root->key))->data;
    }
    return isEnded();
}

template <typename TKey, typename TData>
bool SearchTreeTable<TKey, TData>::next()
{
    if (isEnded()) return true;
    current = root->next(current->key)->data;
    return isEnded();
}

template <typename TKey, typename TData>
bool SearchTreeTable<TKey, TData>::isEnded() const
{
    return ((current == nullptr) || (root->next(current->key) == nullptr));
}

template <typename TKey, typename TData>
TKey SearchTreeTable<TKey, TData>::getKey()
{
    return current->key;
}

template <typename TKey, typename TData>
TData* SearchTreeTable<TKey, TData>::getData()
{
    return current->data;
}

template <typename TKey, typename TData>
bool SearchTreeTable<TKey, TData>::full() const
{
    return false;
}