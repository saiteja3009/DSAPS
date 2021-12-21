#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

char board[10][10];

class Trie
{
	public:
		char c;
	bool end;
	bool found;
	Trie *arr[26];
	string word;
	Trie()
	{
		for (int i = 0; i < 26; i++)
			arr[i] = NULL;
	}

	Trie(char ch, bool flag, string w)
	{
		c = ch;
		end = flag;
		word = w;
		for (int i = 0; i < 26; i++)
			arr[i] = NULL;
	}
};

void insert(Trie *root, string s)
{
	string w = "";
	int i;
	for (i = 0; i < s.length() - 1; i++)
	{
		int x = s[i] - 'a';
		w += s[i];
		if (root->arr[x] == NULL)
		{
			// cout<<x<<" ";
			root->arr[x] = new Trie(s[i], false, w);
		}

		root = root->arr[x];
	}

	int x = s[i] - 'a';
	w += s[i];
	if (root->arr[x] == NULL)
	{
		//cout<<x<<" ";
		root->arr[x] = new Trie(s[i], true, w);
	}
	else
	{
		root = root->arr[x];
		root->end = true;
	}
}

void dfs(Trie *root, int i, int j, int n, int m)
{
	//cout<<board[i][j]<<"\n";
	if (i < 0 || j < 0 || i >= n || j >= m)
		return;
	int x = board[i][j] - 'a';
	if (x < 0 || (root->arr[x]) == NULL)
		return;
	root = root->arr[x];
	if ((root->end) == true)
	{
		root->found = true;
		root->end = false;
	}

	board[i][j] -= 32;
	//cout<<board[i][j]<<"\n";

	if (i - 1 >= 0)
	{
		int p = board[i - 1][j] - 'a';
		if (p >= 0 && root->arr[p] != NULL)
			dfs(root, i - 1, j, n, m);

	}

	if (j - 1 >= 0)
	{
		int p = board[i][j - 1] - 'a';
		if (p >= 0 && root->arr[p] != NULL)
			dfs(root, i, j - 1, n, m);

	}

	if (i + 1 < n)
	{
		int p = board[i + 1][j] - 'a';
		if (p >= 0 && root->arr[p] != NULL)
		{
			//cout<<board[i+1][j]<<"ss\n";
			dfs(root, i + 1, j, n, m);
		}
	}

	if (j + 1 < m)
	{
		//cout<<board[i][j+1]<<" asz\n";
		int p = board[i][j + 1] - 'a';

		//cout<<root->arr[p]->end;
		if (p >= 0 && root->arr[p] != NULL)
		{
			dfs(root, i, j + 1, n, m);
		}
	}

	board[i][j] += 32;
	return;
}

void findWords(Trie *root, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			int p = board[i][j] - 'a';
			if (root->arr[p] != NULL)
			{
				// cout<<board[i][j]<<"\n";
				dfs(root, i, j, n, m);

			}
		}
	}

	return;
}

void printwords(Trie *root)
{
	if (root->found == true)
		cout << root->word << "\n";
	for (int i = 0; i < 26; i++)
	{
		if (root->arr[i] != NULL)
		{
			printwords(root->arr[i]);
		}
	}

	return;
}

int main()
{
	/*Enter your code here. Read input from STDIN. Print output to STDOUT */
	int n, m;
	cin >> n >> m;
	Trie *root = new Trie();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			char ch;
			cin >> ch;
			board[i][j] = ch;
		}
	}

	string k;
	int size;
	cin >> size;
	for (int i = 0; i < size; i++)
	{
		cin >> k;
		insert(root, k);
	}

	findWords(root, n, m);
	printwords(root);
	return 0;
}