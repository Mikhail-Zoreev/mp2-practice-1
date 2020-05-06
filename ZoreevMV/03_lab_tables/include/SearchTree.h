#include <queue>
#include <stack>

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
class SearchTree
{
public:
    Node<TKey, TData>* root;

    SearchTree();
    SearchTree(const SearchTree& temp);
    ~SearchTree();

    //Операци с деревом
    Node<TKey, TData>* find(TKey key_);
    Node<TKey, TData>* findMin(TKey key_);
    Node<TKey, TData>* findMax(TKey key_);
    void insert(TKey key_, const TData* data_);
    void remove(TKey key_);

    Node<TKey, TData>* next(TKey key_);
};

//Методы Node
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

//Методы SearchTree
template<typename TKey, typename TData>
SearchTree<TKey, TData>::SearchTree()
{
    root = nullptr;
}

template<typename TKey, typename TData>
SearchTree<TKey, TData>::SearchTree(const SearchTree& temp)
{
    if (temp->root == nullptr)
    {
        root = nullptr;
        return;
    }
    std::queue<Node<TKey, TData>*> nodes;
    nodes.push(temp->root);
    while (!nodes.empty())
    {
        Node<TKey, TData>* current = nodes.pop();
        insert(current->key, current->data);
        if (current->left != nullptr) nodes.push(current->left);
        if (current->right != nullptr) nodes.push(current->right);
    }
}

template<typename TKey, typename TData>
SearchTree<TKey, TData>::~SearchTree()
{
    if (root == nullptr) return;
    std::stack<Node<TKey, TData>*> nodes;
    nodes.push(root);
    while (!nodes.empty())
    {
        Node<TKey, TData>* current = nodes.top();
        if ((current->left == nullptr) && (current->right == nullptr))
        {
            if (current->parent != nullptr)
            {
                if (current == current->parent->left)
                {
                    current->parent->left = nullptr;
                }
                else
                {
                    current->parent->right = nullptr;
                }
            }
            delete current;
            nodes.pop();
        }
        else
        {
            if (current->left != nullptr) nodes.push(current->left);
            if (current->right != nullptr) nodes.push(current->right);
        }
    }
}

template<typename TKey, typename TData>
Node<TKey, TData>* SearchTree<TKey, TData>::find(TKey key_)
{
    Node<TKey, TData>* current = root;
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
Node<TKey, TData>* SearchTree<TKey, TData>::findMin(TKey key_)
{
    Node<TKey, TData>* current = nullptr;
    if ((current = find(key_)) == nullptr) return nullptr;
    while (current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

template<typename TKey, typename TData>
Node<TKey, TData>* SearchTree<TKey, TData>::findMax(TKey key_)
{
    Node* current = nullptr;
    if (!(current = find(key_))) return nullptr;
    while (current->right != nullptr)
    {
        current = current->right;
    }
    return current;
}

template<typename TKey, typename TData>
void SearchTree<TKey, TData>::insert(TKey key_, const TData* data_)
{
    if (root == nullptr)
    {
        root = new Node<TKey, TData>(key_, data_);
        return;
    }
    Node<TKey, TData>*x = root, *y = root;
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
    }
    Node<TKey, TData>* node = new Node<TKey, TData>(key_, data_);
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

template<typename TKey, typename TData>
void SearchTree<TKey, TData>::remove(TKey key_)
{
    Node<TKey, TData>*node, *y = nullptr, *x = nullptr;
    if ((node = find(key_)) == nullptr) return;
    if ((node->left != nullptr) && (node->right != nullptr))
    {
        y = next(key_);
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

template<typename TKey, typename TData>
Node<TKey, TData>* SearchTree<TKey, TData>::next(TKey key_)
{
    Node<TKey, TData>*node = nullptr, *result = nullptr;
    if ((node = find(key_)) == nullptr) return nullptr;
    if (node->right != nullptr)
    {
        result = findMin(node->right->key);
        return result;
    }
    result = node->parent;
    Node<TKey, TData>* temp = node;
    while ((result != nullptr) && (temp == result->right))
    {
        temp = result;
        result = result->parent;
    }
    return result;
}