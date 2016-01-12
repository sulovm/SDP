#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int LETTERS = 26;

struct Node
{
    int inf;
    vector<Node*> children;

    Node()
    {
        inf = 0;
        for (int i = 0; i < LETTERS; i++)
        {
            Node* node = NULL;
            children.push_back(node);
        }
    }
};

class Trie
{
    Node* root;

public:
    Trie():root(NULL) {}

    Trie (const Trie& other):root(NULL)
    {
        root = copy(other.root);
    }

    ~Trie()
    {
        destroy(root);
    }

    Trie& operator = (const Trie& other)
    {
        if (this != &other)
        {
            destroy(root);
            root = copy(other.root);
        }
        return *this;
    }

    void addWord (string word) {add (root, word);}

    vector <string> getSuggestions (string beginning)
    {
        Node* start = root;
        int beginningSize = beginning.size();
        for (int i = 0; i < beginningSize; i++)
        {
            if (start == NULL)
            {
                return vector<string>();
            }
            int letter = beginning[i] - 'a';
            start = start->children[letter];
        }
        if (start == NULL)
        {
            return vector<string>();
        }

        vector<string> result;
        if (start->inf > 0)
        {
            result.push_back(beginning);
        }
        getSugg(start, beginning, result);
        return result;
    }

    bool find (string word) {return getValue(word) > 0;}

    bool remove (string word)
    {
        if (!find(word)) return false;
        decValue (root, word);
        return true;
    }

    int getValue (string word) {return value (root, word);}

    void print()
    {
        pr(root);
    }

private:
    Node* copy (Node*);
    void destroy(const Node*);
    void add (Node*&, string);
    void getSugg (Node*&, const string&, vector<string>&);
    void decValue (Node*&, string);
    int value (Node*&, string);
    void pr (Node*&);
};

Node* Trie::copy (Node* current)
{
    if (current == NULL) return NULL;
    Node* newNode = new Node();
    newNode -> inf = current -> inf;
    for (int i = 0; i < LETTERS; i++)
    {
        newNode -> children.push_back (copy (current->children[i]));
    }
    return newNode;
}

void Trie::destroy(const Node* current)
{
    if (current == NULL) return;
    if (!current -> children.empty())
        for (int i = 0; i < LETTERS; i++)
        {
            destroy (current->children[i]);
        }
    delete current;
}

void Trie::add (Node*& where, string word)
{
    if (where == NULL)
    {
        where = new Node();
    }
    if (word.empty())
    {
        where -> inf = where -> inf + 1;
        return;
    }

    int letter = word[0] - 'a';
    word.erase(0, 1);
    add (where -> children [letter], word);
}

void Trie::getSugg (Node*& where, const string& sugg, vector<string>& result)
{
    if (where == NULL)
    {
        return;
    }
    for (int i = 0; i < LETTERS; i++)
    {
        if(where->children[i] != NULL)
        {
            char character = (char)(i + 'a');
            string helper = sugg + character;
            if (where->children[i]->inf > 0)
            {
                result.push_back(helper);
            }
            getSugg(where->children[i], helper, result);
        }
    }
}

void Trie::decValue (Node*& where, string word)
{
    if (where)
    {
        if (word.empty())
        {
            where -> inf = where -> inf - 1;
            return;
        }
        int letter = word[0] - 'a';
        word.erase(0, 1);
        decValue (where -> children [letter], word);
    }
}

int Trie::value (Node*& where, string word)
{
    if (where == NULL)
    {
        return 0;
    }
    if (word.empty()) return where -> inf;

    int letter = word[0] - 'a';
    word.erase(0, 1);
    return value (where -> children [letter], word);
}

void Trie::pr (Node*& what)
{
    if (what == NULL) {cout << "Empty!" << endl; return;}
    cout << what -> inf << " ";

    for (int i = 0; i < LETTERS; i++)
    {
        cout << "(";
        pr (what -> children[i]);
        cout << " ";
    }
    cout << ")\n";
}

bool comparator (pair<string, int> p1, pair<string, int> p2) //for the sort
{
    return p1.second > p2.second;
}

//Task 2
void task2()
{
    Trie trie;
    cout << "Task 2:\nEnter text:\n";

    string word;
    while (cin>>word) //only words without white characters
    {
        trie.addWord(word);
    }

    vector<string> words = trie.getSuggestions("");
    vector <pair<string, int> > counted;
    int numberOfWords = words.size();
    for (int i = 0; i < numberOfWords; i++)
    {
        pair<string, int> p(words[i], trie.getValue(words[i]));
        counted.push_back(p);
    }
    cout << "All words:\n";
    for (int i = 0; i < numberOfWords; i++)
    {
        cout << counted[i].first << ": " << counted[i].second << endl;
    }

    sort(counted.begin(), counted.end(), comparator);

    int wantedNumberOfWords = (numberOfWords < 10 ? numberOfWords : 10);
    cout << "\nThe " << wantedNumberOfWords << " most common words:\n";
    for (int i = 0; i < wantedNumberOfWords; i++)
    {
        cout << counted[i].first << endl;
    }

}

int main ()
{
    task2();

    return 0;
}
