#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Trie
{
    public:
        char c;
    bool end;
    int count;
    Trie *arr[26];
    string word;
    Trie()
    {
        for (int i = 0; i < 26; i++)
            arr[i] = NULL;
    }

    Trie(char ch, string w)
    {
        c = ch;
        //end=flag;
        word = w;
        count = 0;
        for (int i = 0; i < 26; i++)
            arr[i] = NULL;
    }
};

void insert(Trie *root, string s)
{
    string w = "";
    for (int i = 0; i < s.length(); i++)
    {
        int x = s[i] - 'a';
        w += s[i];
        if (root->arr[x] == NULL)
        {
            root->arr[x] = new Trie(s[i], w);
        }

        root = root->arr[x];
        root->count += 1;
    }

    root->end = true;
}

int rescount = 0;
vector<string> arrres;
void findall(Trie *root)
{
    if (root == NULL)
        return;
    if (root->end == true)
    {
        arrres.push_back(root->word);
    }

    for (int i = 0; i < 26; i++)
    {
        if (root->arr[i] != NULL)
        {
            findall(root->arr[i]);
        }
    }

    return;
}

bool autocomplete(Trie *root, string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        int x = s[i] - 'a';
        if (root->arr[x] == NULL)
            return false;
        root = root->arr[x];
    }

    rescount = root->count;
    findall(root);
    return true;
}

bool spellcheck(Trie *root, string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        int x = s[i] - 'a';
        if (root->arr[x] == NULL)
            return false;
        root = root->arr[x];
    }

    return root->end;
}

void search(Trie *root, vector<int> prev, string s, char ch)
{
    // cout<<ch<<"\n";
    // for(int i=0;i < prev.size();i++)
    //     cout<<prev[i]<<" ";
    // cout<<"\n";
    vector<int> current(s.length() + 1);
    for (int i = 0; i < s.length() + 1; i++)
        current[i] = prev[i] + 1;
    for (int i = 1; i < s.length() + 1; i++)
    {
        if (ch == s[i - 1])
        {
            current[i] = prev[i - 1];
        }
        else
        {
            current[i] = min(prev[i - 1], min(current[i - 1], prev[i])) + 1;
        }
    }

    if (current[s.length()] <= 3 && root->end == true)
    {
        rescount += 1;
        arrres.push_back(root->word);
    }

    int mini = 999999;
    for (int i = 0; i < s.length(); i++)
    {
        mini = min(mini, current[i]);
    }

    if (mini <= 3)
    {
        for (int i = 0; i < 26; i++)
        {
            char ch = 'a' + i;
            if (root->arr[i] != NULL)
                search(root->arr[i], current, s, ch);
        }
    }
}

void autocorrect(Trie *root, string s)
{
    vector<int> current(s.length() + 1);
    for (int i = 0; i < s.length() + 1; i++)
        current[i] = i;
    for (int i = 0; i < 26; i++)
    {
        char ch = 'a' + i;
        if (root->arr[i] != NULL)
        {
            search(root->arr[i], current, s, ch);
        }
    }
}

int main()
{
    /*Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n;
    cin >> n;
    Trie *root = new Trie();
    string k;
    for (int i = 0; i < n; i++)
    {
        cin >> k;
        insert(root, k);
    }

    int op;
    cin >> op;
    string p;
    cin >> p;
    if (op == 1)
    {
        cout << spellcheck(root, p);
    }
    else if (op == 2)
    {
        if (autocomplete(root, p))
        {
            cout << rescount << "\n";
            for (int i = 0; i < arrres.size(); i++)
            {
                cout << arrres[i] << "\n";
            }
        }
        else
        {
            cout << 0;
        }
    }
    else
    {
        autocorrect(root, p);
        cout << rescount << "\n";
        for (int i = 0; i < arrres.size(); i++)
            cout << arrres[i] << "\n";

    }

    return 0;
}