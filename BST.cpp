
template <class T>
class BST;

template <class T>
class BSTNode
{
public:
    BSTNode(const T &val, BSTNode *left, BSTNode *right);
    T get_val() const { return val; }
    BSTNode *get_left() const { return left; }
    BSTNode *get_right() const { return right; }

private:
    T val;
    BSTNode *left;
    BSTNode *right;

    friend class BST<T>;
};

template <class T>
BSTNode<T>::BSTNode(const T &val,
                    BSTNode *left,
                    BSTNode *right)
{
    this->val = val;
    this->left = left;
    this->right = right;
}

template <class T>
class BST
{
public:
    BST();
    BST(const BST &other);
    ~BST();

    bool is_empty() const;
    bool contains(const T &val) const;

    T max() const;
    T min() const;
    T remove_max();
    T remove_min();

    void insert(const T &val);
    bool remove(const T &val);
    void clear();

    DLList<T> elements() const;
    DLList<T> elements_level_ordered() const;
    BSTNode<T> *get_root() const { return root; }

    BST &operator=(const BST &other);

private:
    BSTNode<T> *root;

    void copy_from(BSTNode<T> *node);
    void elements(DLList<T> &result, BSTNode<T> *node) const;
    bool contains(const T &val, BSTNode<T> *node) const;

    void remove_1(BSTNode<T> *ptr, BSTNode<T> *prev);
    void remove_2(BSTNode<T> *node);

    void clear(BSTNode<T> *node);
};

template <class T>
BST<T>::BST()
{
    root = nullptr;
}

template <class T>
void BST<T>::copy_from(BSTNode<T> *node)
{
    if (node == nullptr)
        return;

    insert(node->val);
    copy_from(node->left);
    copy_from(node->right);
}

template <class T>
BST<T>::BST(const BST<T> &other)
{
    root = nullptr;
    copy_from(other.root);
}

template <class T>
BST<T>::~BST()
{
    clear();
}

template <class T>
bool BST<T>::is_empty() const
{
    return root == nullptr;
}

template <class T>
bool BST<T>::contains(const T &val) const
{
    BSTNode<T> *node = root;

    while (node != nullptr)
    {

        if (val == node->val)
            return true;

        if (val < node->val)
            node = node->left;
        else
            node = node->right;
    }

    return false;
}

template <class T>
bool BST<T>::contains(const T &val, BSTNode<T> *node) const
{

    if (node == nullptr)
        return false;

    if (val == node->val)
        return true;

    if (val < node->val)
        return contains(val, node->left);
    else
        return contains(val, node->right);
}

template <class T>
void BST<T>::insert(const T &val)
{

    if (is_empty())
    {
        root = new BSTNode<T>(val, nullptr, nullptr);
        return;
    }

    BSTNode<T> *curr = root;
    BSTNode<T> *prev = nullptr;

    while (curr != nullptr)
    {
        prev = curr;
        if (val < curr->val)
            curr = curr->left;
        else if (val > curr->val)
            curr = curr->right;
        else
            return;
    }

    BSTNode<T> *new_node = new BSTNode<T>(val, nullptr, nullptr);

    if (val < prev->val)
        prev->left = new_node;
    else
        prev->right = new_node;
}

template <class T>
bool BST<T>::remove(const T &val)
{
    BSTNode<T> *node = root;
    BSTNode<T> *prev = nullptr;

    while (node != nullptr)
    {
        if (node->val == val)
            break;

        prev = node;
        if (val < node->val)
            node = node->left;
        else
            node = node->right;
    }

    if (node == nullptr)
        return false;

    if (node->left == nullptr || node->right == nullptr)
        remove_1(node, prev);
    else
        remove_2(node);

    return true;
}

template <class T>
void BST<T>::remove_1(BSTNode<T> *ptr, BSTNode<T> *prev)
{

    if (ptr == root)
    {

        if (root->left != nullptr)
            root = root->left;
        else
            root = root->right;
    }

    else if (ptr == prev->left)
    {
        if (ptr->right != nullptr)
            prev->left = ptr->right;
        else
            prev->left = ptr->left;
    }

    else
    {
        if (ptr->right != nullptr)
            prev->right = ptr->right;
        else
            prev->right = ptr->left;
    }

    delete ptr;
}

template <class T>
void BST<T>::remove_2(BSTNode<T> *node)
{

    BSTNode<T> *rep = node->left;
    BSTNode<T> *prev = node;

    while (rep->right != nullptr)
    {
        prev = rep;
        rep = rep->right;
    }

    node->val = rep->val;

    remove_1(rep, prev);
}

template <class T>
void BST<T>::clear()
{
    clear(root);
    root = nullptr;
}

template <class T>
void BST<T>::clear(BSTNode<T> *node)
{
    if (node == nullptr)
        return;

    clear(node->left);
    clear(node->right);

    delete node;
}

template <class T>
T BST<T>::max() const
{
    if (is_empty())
        throw string("ERROR: Attempting to retrieve the max value in an empty tree");

    BSTNode<T> *curr = root;
    while (curr->right != nullptr)
        curr = curr->right;

    return curr->val;
}

template <class T>
T BST<T>::min() const
{
    if (is_empty())
        throw string("ERROR: Attempting to retrieve the min value in an empty tree");

    BSTNode<T> *curr = root;
    while (curr->left != nullptr)
        curr = curr->left;

    return curr->val;
}

template <class T>
T BST<T>::remove_max()
{
    if (is_empty())
        throw string("ERROR: Attempting to remove the max value from an empty tree");

    BSTNode<T> *curr = root;
    BSTNode<T> *prev = nullptr;
    while (curr->right != nullptr)
    {
        prev = curr;
        curr = curr->right;
    }

    T val = curr->val;
    remove_1(curr, prev);
    return val;
}

template <class T>
T BST<T>::remove_min()
{
    if (is_empty())
        throw string("ERROR: Attempting to remove the min value from an empty tree");

    BSTNode<T> *curr = root;
    BSTNode<T> *prev = nullptr;
    while (curr->left != nullptr)
    {
        prev = curr;
        curr = curr->left;
    }

    T val = curr->val;
    remove_1(curr, prev);
    return val;
}

template <class T>
BST<T> &BST<T>::operator=(const BST<T> &other)
{

    if (this == &other)
        return *this;

    clear();
    copy_from(other.root);

    return *this;
}