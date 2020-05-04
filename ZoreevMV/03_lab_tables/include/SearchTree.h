template<typename TKey, typename TData>
struct Node
{
    TKey key;
    TData* data;
    Node* left;
    Node* right;
    Node* parent;

    Node(TKey key_, const TData* data_);
    Node(TKey key_, const TData& data_);
    Node(const Node& temp);
};

template<typename TKey, typename TData>
Node<TKey, TData>::Node(TKey key_, const TData* data_)
{
    key = key_;
    data = new TData(*data_);
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

template<typename TKey, typename TData>
Node<TKey, TData>::Node(TKey key_, const TData& data_)
{
    key = key_;
    data = new TData(data_);
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

template<typename TKey, typename TData>
Node<TKey, TData>::Node(const Node& temp)
{
    key = temp.key;
    data = new TData(temp.data);
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}


template<typename TKey, typename TData>
class SearchTree
{
    Node<TKey, TData>* root;

public:
    SearchTree();
    SearchTree(const SearchTree& temp);
    ~SearchTree();

    //Операци с деревом
    Node<TKey, TData>* find(TKey key_);
    void insert(TKey key_, TData* data_);
    void remove(TKey key_);
};

template<typename TKey, typename TData>
SearchTree<TKey, TData>::SearchTree()
{
    root = nullptr;
}

template<typename TKey, typename TData>
SearchTree<TKey, TData>::SearchTree(const SearchTree& temp)
{
    //TODO: Реализация
}

template<typename TKey, typename TData>
SearchTree<TKey, TData>::~SearchTree()
{
    //TODO: Реализация
}

template<typename TKey, typename TData>
Node<TKey, TData>* SearchTree<TKey, TData>::find(TKey key_)
{
    Node* current = root;
    while ((current != nullptr) && (current->key != key_))
    {
        if (key_ < current->key)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return current;
}

template<typename TKey, typename TData>
void SearchTree<TKey, TData>::insert(TKey key_, TData* data_)
{
    if (root == nullptr)
    {
        root = new Node(key_, data_);
        return;
    }
    Node *x = root, *y;
    while (x != nullptr)
    {
        y = x;
        if (key_ < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
        Node* node = new Node(key_, data_);
        node->parent = y;
        if (node->key < y->key)
        {
            y->left = node;
        }
        else
        {
            y->right = node;
        }   
    }
}

template<typename TKey, typename TData>
void SearchTree<TKey, TData>::remove(TKey key_)
{
    Node *node, *y = nullptr, *x = nullptr;
    if ((node = find(key_)) == nullptr) return;
    if ((node->left != nullptr) && (node->right !=) nullptr)
    {
        //y = next(key)
    }
    else
    {
        y = node;
    }
    if (y->left != nullptr)
    {
        x = y->left;
    }
    else
    {
        x = y->right;
    }
    if (x != nullptr) x->parent = y->parent;
    if (y->parent != nullptr)
    {
        if (y == y->parent->left) y->parent->left = x;
        else y->parent->right = x;
    }
    if (y != node)
    {
        node->key = y->key;
        delete node->data;
        node->data = y->data;
    }
}