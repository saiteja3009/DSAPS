#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, ll> pii;
typedef vector<int> vi;

struct SuffixArray
{
    vi sa, lcp;
    SuffixArray(string &s, int lim = 256)
    { 
        int n = sz(s) + 1, k = 0, a, b;
        vi x(all(s) + 1), y(n), ws(max(n, lim)), rank(n);
        sa = lcp = y, iota(all(sa), 0);
        for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p)
        {
            p = j, iota(all(y), n - j);
            rep(i, 0, n) if (sa[i] >= j) y[p++] = sa[i] - j;
            fill(all(ws), 0);
            rep(i, 0, n) ws[x[i]]++;
            rep(i, 1, lim) ws[i] += ws[i - 1];
            for (int i = n; i--;)
                sa[--ws[x[y[i]]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            rep(i, 1, n) a = sa[i - 1], b = sa[i], x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
        }
        rep(i, 1, n) rank[sa[i]] = i;
        for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
            for (k &&k--, j = sa[rank[i] - 1];
                 s[i + k] == s[j + k]; k++)
                ;
    }
};
signed main()
{
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    string str;
    
    cin >> str;
    int n=str.length();
    string strrev=str;
    reverse(strrev.begin(),strrev.end());
    str+='#'+strrev;
    SuffixArray suf(str);

    vector<int> sa = suf.sa, lcp = suf.lcp;

    vector<int> rank(2*n+1);
    for(int i=0;i<2*n+1;i++){
        rank[sa[i]]=i;
    }

    int ans=1;
    int index=sa[2];
    for(int i=0;i<n;i++)
    {
       // cout<<i;
        int odd=2*n-i;
        int even=2*n-i+1;
        int x=99999;

        for(int j=rank[i]+1;j<=rank[odd];j++){
            x=min(lcp[j],x);
        }
        //cout<<x<<endl;;
        if(x!=99999)
            {
               if(x>ans)
               {
                   ans=x;
                   index=i-ans+1;
               }
                
            }

    }
    cout<<ans*2-1<<endl;
    cout<<str.substr(index,2*ans-1);

          
}