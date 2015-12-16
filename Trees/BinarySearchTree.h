#include <ostream>

template<typename T>
struct node
{
    T data;
    node* left;
    node* right;

    node(T _data) {left = NULL; right = NULL; data = _data;}
};

template<typename T>
class BST
{
    node<T>* root;
public:
    BST():root(NULL) {}

    BST(const BST& other):root(NULL)
    {
        copy(other.root, root);
    }
    BST& operator=(const BST& other);

    ~BST()
    {
        destroy(root);
    }

     bool isEmpty() const
    {
        return root == NULL;
    }
    void addElement(const T& element)
    {
        addElement(root, element);
    }
    T findMin() const
    {
        return findMin(root);
    }
    T findMax() const
    {
        return findMax(root);
    }
    bool isElement(const T& element) const
    {
        return isElement(root, element);
    }
    void remove(const T& element)
    {
        if (!isElement(element))
        {
            return;
        }
        remove(root, element);
    }
    std::ostream& print(std::ostream& out) const
    {
        return print(out, root);
    }
private:
    void copy(node<T>* what, node<T>*& where);
    void destroy(node<T>*& what);
    void addElement(node<T>*& where, const T& element);
    T findMin(node<T>* where) const;
    T findMax(node<T>* where) const;
    bool isElement(node<T>* where, const T& element) const;
    void removeMin(node<T>*& where);
    void remove(node<T>*& where, const T& element);
    std::ostream& print(std::ostream& out, node<T>* what) const;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const BST<T>& bst)
{
    if(bst.isEmpty())
    {
        out << "[]";
        return out;
    }
    bst.print(out);
    return out;
}

template<typename T>
std::ostream& BST<T>::print(std::ostream& out, node<T>* what) const
{
    if (what == NULL)
    {
        return out;
    }
    out << "[";
    print(out, what->left) << " ";
    out << what->data << " ";
    print(out, what->right);
    out << "]";

    return out;
}

template<typename T>
void BST<T>::remove(node<T>*& where, const T& element)
{
    if (where == NULL)
    {
        return;
    }
    if(element == where->data)
    {
        if(where->left == NULL || where->right == NULL)
        {
            node<T>* p = where;
            if(where->left == NULL)
            {
                where = where->right;
            }
            else
            {
                where = where->left;
            }
            delete p;
        }
        else
        {
            T helper = findMin(where->right);
            removeMin(where->right);
            where->data = helper;
        }
        return;
    }
    if (element < where->data)
    {
        remove(where->left, element);
        return;
    }
    remove(where->right, element);
}

template<typename T>
void BST<T>::removeMin(node<T>*& where)
{
    if (where->left == NULL)
    {
        node<T>* p = where;
        where = where->right;
        delete p;
        return;
    }
    removeMin(where->left);
}

template<typename T>
bool BST<T>::isElement(node<T>* where, const T& element) const
{
    if (where == NULL)
    {
        return false;
    }
    if (element == where->data)
    {
        return true;
    }
    if (element > where->data)
    {
        return isElement(where->right, element);
    }
    return isElement(where->left, element);
}

template<typename T>
T BST<T>::findMin(node<T>* where) const
{
    if (where->left == NULL)
    {
        return where->data;
    }
    return findMin(where->left);
}

template<typename T>
T BST<T>::findMax(node<T>* where) const
{
    if (where->right == NULL)
    {
        return where->data;
    }
    return findMax(where->right);
}

template<typename T>
void BST<T>::addElement(node<T>*& where, const T& element)
{
    if (where == NULL)
    {
        where = new node<T>(element);
        return;
    }
    if (element == where->data)
    {
        return;
    }
    if (element > where->data)
    {
        addElement(where->right, element);
        return;
    }
    addElement(where->left, element);
}

template<typename T>
void BST<T>::destroy(node<T>*& what)
{
    if (what == NULL)
    {
        return;
    }
    if (what->left == NULL && what->right == NULL)
    {
        delete what;
        what = NULL;
        return;
    }
    if (what->left != NULL)
    {
        destroy(what->left);
    }
    if (what->right != NULL)
    {
        destroy(what->right);
    }
    delete what;
    what = NULL;
}

template<typename T>
void BST<T>::copy(node<T>* what, node<T>*& where)
{
    if (what == NULL)
    {
        return;
    }
    where = new node<T>(what->data);
    if (what->left != NULL)
    {
        copy(what->left, where->left);
    }
    if (what->right != NULL)
    {
        copy(what->right, where->right);
    }
}

template<typename T>
BST<T>& BST<T>::operator=(const BST& other)
{
    if (this != &other)
    {
        destroy(root);
        copy(other.root, root);
    }
    return *this;
}
