#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<pair<int,string>>res;
void allpath(vector<vector<pair<int,int>>>&g,int n,int m,vector<bool>&vis,vector<bool> end,string current,int cost,int i)
{   
    vis[i]=true;
    current=current+to_string(i)+" ";
    if(!end[i] && cost>0)
    {
        res.push_back({cost,current});
    }
    for(pair<int,int> x:g[i])
        if(!vis[x.first])
            allpath(g,n,m,vis,end,current,cost+x.second,x.first);
    vis[i]=false;
    return;
}

void kshort(vector<vector<pair<int,int>>> &g,int n,int m,int k)
{
    
    vector<bool> vis(n,false);
    vector<bool> end(n,false);
    for(int i=0;i<n;i++){
        allpath(g,n,m,vis,end,"",0,i);
        end[i]=true;
    }
    sort(res.begin(),res.end());
    int size=res.size();
    for(int i=0;i<min(k,size);i++)
    {
        cout<<res[i].second<<"\n";
    }
    return;
}



int main() {
    int n,m;
    cin>>n>>m;
        vector<vector<pair<int,int>>> g(n);
    int x=m;
        while(x--){
            int u,v,w;
            cin>>u>>v>>w;
            g[u].push_back(make_pair(v,w));
            g[v].push_back(make_pair(u,w));
        }
        int k;
        cin>>k;
        kshort(g,n,m,k);
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}
