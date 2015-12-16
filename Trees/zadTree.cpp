#include <iostream>
#include <vector>
#include <fstream>
#include <assert.h>
using namespace std;
/*
Дърво е:
1/ Празното дърво е дърво
2/ Нека t1,...,tk са дървета, а x e елемент, тогава
структурата от данни
x
/ | ... \
t1 t2 .. tk
наричам дърво с корен x и поддървета t1,...tk
*/
template <class T>
void printVector(vector<T>& v)
{
    cout << "[";
    int n = v.size();
    for (int i = 0; i < n - 1; i++)
            cout << v[i] << "; ";
    if (n > 0) cout << v[n - 1];
    cout << "]\n";
}

template <class ElemType>
struct TreeNode
{
    ElemType x;
    vector<TreeNode<ElemType>* > children;
    int uid;
    TreeNode ()
    {
        static int currentId = 0;
        uid = currentId;
        currentId++;
    }
};
template <class T>
class Tree
{
private:
    TreeNode<T> *root;
public:
    Tree ():root (NULL)
    {}
    Tree (const Tree<T>& t)
    {
        root = copyTree (t.root);
    }
    Tree<T>& operator = (const Tree<T> &t)
    {
        if (this != &t)
    {
    destroy (root);
    root = copyTree (t.root);
    }
        return *this;
    }
    ~Tree ()
    {
        destroy (root);
    }
    bool empty ()
    {
        return root == NULL;
    }
    void setRoot (const T& newRoot)
    {
    /*
    Tree<int> t;
    t.setRoot (2);
    t.setRoot (3);
    */
        if (root == NULL)
        {
            root = new TreeNode<T>;
        }
        root->x = newRoot;
    }

    void addSubTree (const Tree<T>& t)
    {
        assert (root != NULL);
        root->children.push_back (copyTree(t.root));
    }

    void print (ostream &out)
    {
        out << "digraph{" << endl;
        printNode (out,root);
        out << "}";
    }

    int height()
    {
        return heightIter (root);
    }

    int count()
    {
        return counter (root);
    }

    int countLeaves()
    {
        return counterOfLeaves (root);
    }

    T sum (const T& null_val)
    {
        return sumator (null_val, root);
    }

    vector<T>& leaves(vector<T>& result)
    {
        //vector<T> result;
        if (!result.empty()) result.clear();
        vectorOfLeaves (root, result);
        return result;
    }

    vector<T>& level (int k, vector<T>& result)
    {
        //vector<T> result;
        if (!result.empty()) result.clear();
        if (k < 1 || k > height()) return result;
        vectorLevel (k, root, result);
        return result;
    }

    void insertSorted (const T& x) //за ДНД
    {
        insertSortedIter(x, root);
    }

    void extremum()
    {
        cout << "Min: " << minEl (root) << endl;
        cout << "Max: " << maxEl (root) << endl;
    }

    bool isBOT()
    {
        return isBinOrdTr (root);
    }

    bool memberBOT (const T& x)
    {
        isMemberBOT (x, root);
    }

    bool memberGeneral (const T& x)
    {
        isMember (x, root);
    }

private:
    void printNode (ostream &out,const TreeNode<T> *currentNode)
    {
        if (currentNode == NULL)
        return;
        out << currentNode->uid
            << "[label=\"val="
            << currentNode->x
            << "\"];"
            << endl;
        for (int i = 0; i < currentNode->children.size(); i++)
        if (currentNode->children[i] != NULL)
        {
            out << currentNode->uid
                << " -> "
                << currentNode->children[i]->uid
                << endl;
            printNode (out, currentNode->children[i]);
        }
    }

    void destroy (const TreeNode<T> *currentNode)
    {
        if (currentNode == NULL)
        return;
        for (int i = 0; i < currentNode->children.size(); i++)
        {
            destroy (currentNode->children[i]);
        }
        delete currentNode;
    }

    TreeNode<T> *copyTree (const TreeNode<T> *currentNode)
    {
        if (currentNode == NULL)
        return NULL;
        TreeNode<T> *newNode = new TreeNode<T>;
        newNode->x = currentNode->x;
        for (int i = 0; i < currentNode->children.size(); i++)
        {
            newNode->children.push_back (copyTree(currentNode->children[i]));
        }
        return newNode;
    }

    int heightIter(const TreeNode<T>* root)
    {
        if (root == NULL) return 0;
        int max = 0;
        for (int i = 0; i < root->children.size(); i++)
        if (heightIter(root->children[i]) > max)
                max = heightIter(root->children[i]);
        return max + 1;
    }

    int counter (const TreeNode<T>* root)
    {
        if (root == NULL) return 0;
        int count = 1;
        for (int i = 0; i < root->children.size(); i++)
                count += counter (root->children[i]);
        return count;
    }

    int counterOfLeaves (const TreeNode<T>* root)
    {
        if (root == NULL) return 0;
        if (root->children.empty()) return 1;
        int count = 0;
        for (int i = 0; i < root->children.size(); i++)
                count += counterOfLeaves (root->children[i]);
        return count;
    }

    T sumator (const T& null_val, const TreeNode<T>* root)
    {
        if (root == NULL) return null_val;
        int sum = null_val + root -> x;
        for (int i = 0; i < root->children.size(); i++)
                sum += sumator (null_val, root->children[i]);
        return sum;
    }

    void vectorOfLeaves (const TreeNode<T>* root, vector<T>& res)
    {
        //vector<T> res;
        if (root == NULL) return;
        if (root->children.empty())
        {
            //cout << "Control: " << root -> x << endl;
            res.push_back(root -> x);
            return;
        }
        for (int i = 0; i < root->children.size(); i++)
                vectorOfLeaves (root->children[i], res);
    }

    void vectorLevel (int k, const TreeNode<T>* root, vector<T>& res)
    {
        //if (k == 0) return res;
        if (k == 1)
        {
            res.push_back(root -> x);
            return;
        }
        for (int i = 0; i < root->children.size(); i++)
                vectorLevel (k - 1, root->children[i], res);
    }

    void insertSortedIter (const T& x, TreeNode<T>* root)
    {
        if (root == NULL)
        {
            root = new TreeNode<T>;
            root -> x = x;
            return;
        }
        //if (x == root->x) return;
        if (root -> children.empty())
        {
            if (x != root -> x)
            {
                TreeNode<T>* node = new TreeNode<T>;
                node -> x = x;
                root -> children.push_back (node);
            }
            return;
        }
        if (root -> children.size() == 1)
        {
            if (root -> children[0] -> x > root -> x)
            {
                if (x < root -> x)
                {
                    TreeNode<T>* temp = root -> children[0];
                    destroy (root -> children[0]);
                    root -> children[0] = new TreeNode<T>;
                    root -> children[0] -> x = x;
                    root -> children.push_back (temp);
                    return;
                }
                if (x > root -> x) insertSortedIter(x, root -> children[0]);
                return;
            }
            if (root -> children[0] -> x < root -> x)
            {
                if (x < root -> x)
                {
                    insertSortedIter(x, root -> children[0]);
                    return;
                }
                if (x > root -> x)
                {
                    TreeNode<T>* node = new TreeNode<T>;
                    node -> x = x;
                    root -> children.push_back (node);
                }
                return;
            }
            return;
        }
        if (x < root -> x) insertSortedIter(x, root -> children[0]);
        if (x > root -> x) insertSortedIter(x, root -> children[1]);
    }

    bool isBinOrdTr (TreeNode<T>* root)
    {
        if (root == NULL) return true;
        if (root -> children.empty()) return true;
        if (root -> children.size() > 2) return false;
        if (root -> children.size() == 1)
        {
            if (root -> children[0] -> x < root -> x)
                return maxEl(root -> children[0]) < root -> x && isBinOrdTr (root -> children[0]);
            if (root -> children[0] -> x > root -> x)
                return minEl(root -> children[0]) > root -> x && isBinOrdTr (root -> children[0]);
        }
        return maxEl(root -> children[0]) < root -> x && isBinOrdTr (root -> children[0]) &&
                minEl(root -> children[1]) > root -> x && isBinOrdTr (root -> children[1]);
    }

    T maxEl (TreeNode<T>* root)
    {
        T max = root -> x;
        if (root -> children.empty()) return max;
        for (int i = 0; i < root -> children.size(); i++)
            if (max < maxEl (root -> children[i])) max = maxEl (root -> children[i]);
        return max;
    }

    T minEl (TreeNode<T>* root)
    {
        T min = root -> x;
        if (root -> children.empty()) return min;
        for (int i = 0; i < root -> children.size(); i++)
            if (min > minEl (root -> children[i])) min = minEl (root -> children[i]);
        return min;
    }

    bool isMemberBOT (const T& x, const TreeNode<T>* root)
    {
        if (root == NULL) return false;
        if (root -> x == x) return true;
        if (root -> children.size() == 0) return false;
        if (root -> children.size() == 1)
        {
            if (root -> children[0] -> x > root -> x && x < root -> x) return false;
            if (root -> children[0] -> x < root -> x && x > root -> x) return false;

            return isMemberBOT (x, root -> children[0]);
        }
        if (x < root -> x) return isMemberBOT (x, root -> children[0]);
        return isMemberBOT (x, root -> children[1]);
    }

    bool isMember (const T& x, const TreeNode<T>* root)
    {
        if (root == NULL) return false;
        if (root -> x == x) return true;
        if (root -> children.size() == 0) return false;
        for (int i = 0; i < root -> children.size(); i++)
            if (isMember (x, root -> children[i])) return true;
        return false;
    }
};
int main ()
{
        Tree<int> t,t1,t2,t3;
        t1.setRoot (2);
        t2.setRoot (10);
        t3.setRoot (8);
        t2.addSubTree (t3);
        if (t.empty())
        cout << "empty" << endl;
        t.setRoot (7);
        t.addSubTree (t1);
        t.addSubTree (t2);
        ofstream dotfile ("result.dot");
        //t3.setRoot (2000);
        t.print (dotfile);
        t.print (cout);
        /*cout << "Height: " << t.height() << endl;
        cout << "Number of elements: " << t.count() << endl;
        cout << "Number of leaves: " << t.countLeaves() << endl;
        cout << "Sum of elements: " << t.sum(0) << endl;
        cout << "Vector of leaves:\n";
        vector<int> res;
        printVector (t.leaves(res));
        int k;
        cout << "Insert k: "; cin >> k;
        cout << "Vector of elements on level " << k << ":\n";
        printVector (t.level(k, res));*/

        cout << "==========================================================\n";
        t.insertSorted (3);
        t.print (cout);
        //t.extremum();
        cout << "============================================================\n";
        t.insertSorted (9);
        t.print (cout);
        t.extremum();
        cout << boolalpha << t.isBOT() << endl;
        cout << "============================================================\n";
        cout << boolalpha << t.memberBOT (3) << endl;
        cout << boolalpha << t.memberGeneral (11) << endl;

        return 0;
}


